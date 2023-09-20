// Copyright (c) 2021 LootLocker


#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerConfig.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Utils/LootLockerUtilities.h"

const FString ULootLockerHttpClient::UserAgent = FString::Format(TEXT("X-UnrealEngine-Agent/{0}"), { ENGINE_VERSION_STRING });
const FString ULootLockerHttpClient::UserInstanceIdentifier = FGuid::NewGuid().ToString();

ULootLockerHttpClient::ULootLockerHttpClient()
{

}

void ULootLockerHttpClient::LogFailedRequestInformation(const FLootLockerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data)
{
    FString LogString = FString::Format(TEXT("{0} request to {1} failed"), { RequestMethod, Endpoint });
    const bool IsInformativeError = !Response.ErrorData.Code.IsEmpty();
    if(IsInformativeError)
    {
        LogString += FString::Format(TEXT("\n   {0}"), { Response.ErrorData.Message });
        LogString += FString::Format(TEXT("\n    Error Code: {0}"), { Response.ErrorData.Code });
        LogString += FString::Format(TEXT("\n    Further Information: {0}"), { Response.ErrorData.Doc_url });
        LogString += FString::Format(TEXT("\n    Request ID: {0}"), { Response.ErrorData.Request_id });
        LogString += FString::Format(TEXT("\n    Trace ID: {0}"), { Response.ErrorData.Trace_id });
    }
    LogString += FString::Format(TEXT("\n   HTTP Status code : {0}"), { Response.StatusCode });
    if (!Data.IsEmpty()) {
        LogString += FString::Format(TEXT("\n   Request Data: {0}"), { LootLockerUtilities::ObfuscateJsonStringForLogging(Data) });
    }

	if(!IsInformativeError)
    {
        LogString += FString::Format(TEXT("\n   Response Data: {0}"), { Response.FullTextFromServer });
    }
    LogString += "\n###";
	UE_LOG(LogLootLockerGameSDK, Warning, TEXT("%s"), *LogString);
}

bool ULootLockerHttpClient::ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful)
{
    if (!bWasSuccessful || !InResponse.IsValid())
        return false;

    return EHttpResponseCodes::IsOk(InResponse->GetResponseCode());
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

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, endPoint, requestType, data](FHttpRequestPtr Req, const FHttpResponsePtr& Response, bool bWasSuccessful)
	{
		FLootLockerResponse response;
        
        response.success = ResponseIsValid(Response, bWasSuccessful);
        response.StatusCode = response.ServerCallStatusCode = Response->GetResponseCode();
		response.FullTextFromServer = Response->GetContentAsString();
		if (!response.success)
		{
            FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerErrorData>(response.FullTextFromServer, &response.ErrorData, 0, 0);
            response.Error = response.ErrorData.Message;
            LogFailedRequestInformation(response, requestType, endPoint, data);
		}
		onCompleteRequest.ExecuteIfBound(response);
	});
	Request->ProcessRequest();
}

void ULootLockerHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>& AdditionalFields, const FResponseCallback& onCompleteRequest, TMap<FString, FString> customHeaders) const
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
        onCompleteRequest.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerResponse>(FString::Format(TEXT("Could not read file {0}"), { FilePath })));
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

    Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, requestType, endPoint](FHttpRequestPtr Req, const FHttpResponsePtr& Response, bool bWasSuccessful)
        {
            FLootLockerResponse response;

            response.success = ResponseIsValid(Response, bWasSuccessful);
            response.StatusCode = response.ServerCallStatusCode = Response->GetResponseCode();
            response.FullTextFromServer = Response->GetContentAsString();
            if (!response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerErrorData>(response.FullTextFromServer, &response.ErrorData, 0, 0);
                response.Error = response.ErrorData.Message;
                LogFailedRequestInformation(response, requestType, endPoint, FString("Data Stream"));
            }

            onCompleteRequest.ExecuteIfBound(response);
        });
    Request->ProcessRequest();
}
