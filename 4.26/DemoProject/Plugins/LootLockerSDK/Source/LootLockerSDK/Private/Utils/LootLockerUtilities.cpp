// Copyright (c) 2021 LootLocker

#include "LootLockerUtilities.h"

#include "JsonObjectConverter.h"

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

    TArray<TSharedPtr<FJsonValue>> SerializeMissionCheckpoints(const TArray<FLootLockerMissionCheckpoint>& Checkpoints)
    {
        TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
        for (int i = 0; i < Checkpoints.Num(); i++)
        {
            TSharedPtr<FJsonObject> JsonCheckPoint = FJsonObjectConverter::UStructToJsonObject(Checkpoints[i]);
            JsonCheckPoint->RemoveField("parameters");
            for (auto KeyValuePair : Checkpoints[i].parameters) {
                JsonCheckPoint->SetStringField(KeyValuePair.Key, KeyValuePair.Value);
            }
            
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(JsonCheckPoint)));
        }
        return ItemsJsonArray;
    }

    FString SerializeMission(const FAMission& Mission)
    {
        FString Result;
        TSharedPtr<FJsonObject> MissionJson = FJsonObjectConverter::UStructToJsonObject(Mission);
        
        TArray<TSharedPtr<FJsonValue>> CheckpointsArray = LootLockerUtilities::SerializeMissionCheckpoints(Mission.checkpoints);
        MissionJson->RemoveField("checkpoints");
        MissionJson->SetArrayField("checkpoints", CheckpointsArray);
        
        if (Mission.poster_path.IsEmpty()) {
            MissionJson->RemoveField("poster_path");
        }
        if (Mission.round_length.IsEmpty()) {
            MissionJson->RemoveField("round_length");
        }
        if (Mission.difficulty_name.IsEmpty()) {
            MissionJson->RemoveField("difficulty_name");
        }
        if (Mission.rounds < 0) {
            MissionJson->RemoveField("rounds");
        }
        if (Mission.completion_bonus < 0) {
            MissionJson->RemoveField("completion_bonus");
        }
        if (Mission.difficulty_multiplier < 0) {
            MissionJson->RemoveField("difficulty_multiplier");
        }
        if (Mission.time_score_multiplier < 0) {
            MissionJson->RemoveField("time_score_multiplier");
        }
        
        TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Result);
        FJsonSerializer::Serialize(MissionJson.ToSharedRef(), Writer);
        
        return Result;
    }

    FString SerializeTrigger(const FATriggerPayload& Trigger)
    {
        FString Result;
        TSharedPtr<FJsonObject> TriggerJson = FJsonObjectConverter::UStructToJsonObject(Trigger);
        
        TArray<TSharedPtr<FJsonValue>> RewardsJson = TriggerJson->GetArrayField("rewards");
        for (int i = 0; i < RewardsJson.Num(); i++) {
            TSharedPtr<FJsonObject> temp = RewardsJson[i]->AsObject();
            FATriggerReward reward = Trigger.rewards[i];
            
            if (reward.asset_id < 0) {
                temp->RemoveField("asset_id");
            }
            if (reward.asset_variation_id < 0) {
                temp->RemoveField("asset_variation_id");
            }
            if (reward.score < 0) {
                temp->RemoveField("score");
            }
            if (reward.asset_image.IsEmpty()) {
                temp->RemoveField("asset_image");
            }
            if (reward.asset_name.IsEmpty()) {
                temp->RemoveField("asset_name");
            }
            
            RewardsJson[i] = MakeShareable(new FJsonValueObject(temp));
        }
        
        TriggerJson->SetArrayField("rewards", RewardsJson);
        
        TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Result);
        FJsonSerializer::Serialize(TriggerJson.ToSharedRef(), Writer);
        
        return Result;
    }
}
