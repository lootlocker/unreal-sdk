// Copyright (c) 2021 LootLocker


#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerConfig.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Interfaces/IHttpResponse.h"
#include "Launch/Resources/Version.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"

const FString ULootLockerHttpClient::UserAgent = FString::Format(TEXT("X-UnrealEngine-Agent/{0}"), { ENGINE_VERSION_STRING });
const FString ULootLockerHttpClient::UserInstanceIdentifier = FGuid::NewGuid().ToString();

ULootLockerHttpClient::ULootLockerHttpClient()
{

}

void ULootLockerHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, TMap<FString, FString> customHeaders) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif
	Request->SetURL(endPoint);

	Request->SetHeader(TEXT("User-Agent"), UserAgent);
	Request->SetHeader(TEXT("User-Instance-Identifier"), UserInstanceIdentifier);
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

    for (TTuple<FString, FString> CustomHeader : customHeaders)
    {
        Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
    }

	Request->SetVerb(requestType);
    Request->SetContentAsString(data);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, endPoint, requestType, data](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		FLootLockerResponse response;
        
        response.success = ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, data);
		response.FullTextFromServer = Response->GetContentAsString();
		if (!response.success)
		{
            FLootLockerErrorResponse errorResponse;
            FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerErrorResponse>(response.FullTextFromServer, &errorResponse, 0, 0);
            response.Error = FString::Format(TEXT("{0}: {1}. Trace Id: {2}"), { errorResponse.Error.IsEmpty() ? "UNKNOWN" : errorResponse.Error, errorResponse.Message.IsEmpty() ? "N/A" : errorResponse.Message, errorResponse.trace_id.IsEmpty() ? "N/A" : errorResponse.trace_id });
		}
		response.ServerCallStatusCode = Response->GetResponseCode();
		onCompleteRequest.ExecuteIfBound(response);
	});
	Request->ProcessRequest();
}

bool ULootLockerHttpClient::ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful, FString RequestMethod, FString Endpoint, FString Data)
{
	if (!bWasSuccessful || !InResponse.IsValid())
		return false;

	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode()))
	{
		return true;
	}
	else
	{
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Response returned error code: %d"), InResponse->GetResponseCode());
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Response content:\n%s"), *InResponse->GetContentAsString());
        UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Request endpoint: %s to %s"), *RequestMethod, *Endpoint);
        UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Request data: %s"), *Data);
		return false;
	}
}

void ULootLockerHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString> AdditionalFields, const FResponseCallback& onCompleteRequest, TMap<FString, FString> customHeaders) const
{
    FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif
	Request->SetURL(endPoint);

    FString Boundary = "lootlockerboundary";

	Request->SetHeader(TEXT("User-Agent"), UserAgent);
	Request->SetHeader(TEXT("User-Instance-Identifier"), UserInstanceIdentifier);
    Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=" + Boundary));

    for (TTuple<FString, FString> CustomHeader : customHeaders)
    {
        Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
    }

    Request->SetVerb(requestType);

    TArray<uint8> UpFileRawData;
    if (!FFileHelper::LoadFileToArray(UpFileRawData, *FilePath)) {
        FLootLockerResponse FailResponse;
        FailResponse.success = false;
        FailResponse.FullTextFromServer = FString::Format(TEXT("Could not read file {0}"), { FilePath });
        FailResponse.Error = FailResponse.FullTextFromServer;

        onCompleteRequest.ExecuteIfBound(FailResponse);
        return;
    }

    TArray<uint8> Data;

    const FString BeginBoundary = TEXT("\r\n--" + Boundary + "\r\n");
    const FString EndBoundary = TEXT("\r\n--" + Boundary + "--\r\n");

    for (auto& KeyValuePair : AdditionalFields) {
        Data.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());

        FString ParameterEntry = "Content-Type: text/plain; charset=\"utf-8\"\r\n";
        ParameterEntry.Append(TEXT("Content-Disposition: form-data; name=\""));
        ParameterEntry.Append(KeyValuePair.Key);
        ParameterEntry.Append(TEXT("\"\r\n\r\n"));
        ParameterEntry.Append(KeyValuePair.Value);

        Data.Append((uint8*)TCHAR_TO_ANSI(*ParameterEntry), ParameterEntry.Len());
    }

    Data.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());

    FString FileHeader = (TEXT("Content-Type: application/octet-stream\r\n"));
    FileHeader.Append(TEXT("Content-disposition: form-data; name=\"file\"; filename=\""));

    int32 LastSlashPos = 0;
    FilePath.FindLastChar('/', LastSlashPos);
    if (LastSlashPos == -1) {
        FilePath.FindLastChar('\\', LastSlashPos);
    }
    FString FileName = FilePath.RightChop(LastSlashPos + 1);

    FileHeader.Append(FileName + "\"\r\n\r\n");

    Data.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());
    Data.Append(UpFileRawData);
    Data.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

    Request->SetContent(Data);

    Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, requestType, endPoint](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            const FString ResponseString = Response->GetContentAsString();
            FLootLockerResponse response;

            response.FullTextFromServer = Response->GetContentAsString();
            response.ServerCallStatusCode = Response->GetResponseCode();

            response.success = ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, FString("Data Stream"));
            if (!response.success)
            {
                FLootLockerErrorResponse errorResponse;
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerErrorResponse>(response.FullTextFromServer, &errorResponse, 0, 0);
                response.Error = FString::Format(TEXT("{0}: {1}. Trace Id: {2}"), { errorResponse.Error.IsEmpty() ? "UNKNOWN" : errorResponse.Error, errorResponse.Message.IsEmpty() ? "N/A" : errorResponse.Message, errorResponse.trace_id.IsEmpty() ? "N/A" : errorResponse.trace_id });
            }

            onCompleteRequest.ExecuteIfBound(response);
        });
    Request->ProcessRequest();
}
