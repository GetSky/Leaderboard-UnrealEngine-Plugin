// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PluginSettings.generated.h"

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Leadboard Plugin"))
class GETSKYLEADERBOARD_API UPluginSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Server")
	FString URI;

	UPROPERTY(Config, EditAnywhere, Category = "Server")
	FString Port;
	
	UPROPERTY(Config, EditAnywhere, Category = "Server")
	bool TLS;
};
