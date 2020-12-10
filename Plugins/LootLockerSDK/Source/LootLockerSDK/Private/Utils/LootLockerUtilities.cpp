
#include "LootLockerUtilities.h"

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter)
    {
        FString AppendSymbol = Url.Contains("?") ? "&" : "?";
        return Url + AppendSymbol + Parameter;
    }

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson)
    {
        TArray<FLootLockerMissionCheckpoint> Checkpoints;
        
        TArray<TSharedPtr<FJsonValue>> CheckPointsJson = MissionJson->GetArrayField("checkpoints");
        for (int i = 0; i < CheckPointsJson.Num(); i++) {
            TSharedPtr<FJsonObject> temp = CheckPointsJson[i]->AsObject();
            TMap<FString, FString> parameters;
            FLootLockerMissionCheckpoint checkpoint;
            for (auto FormDataIt = temp->Values.CreateIterator(); FormDataIt; ++FormDataIt)
            {
                FString Key = FormDataIt.Key();
                if (Key == "index") {
                    checkpoint.index = (int) FormDataIt.Value().Get()->AsNumber();
                } else if (Key == "time") {
                    checkpoint.time = (int) FormDataIt.Value().Get()->AsNumber();
                } else {
                    parameters.Add(Key, FormDataIt.Value().Get()->AsString());
                }
            }
            checkpoint.parameters = parameters;
            Checkpoints.Add(checkpoint);
        }
        
        return Checkpoints;
    }
}
