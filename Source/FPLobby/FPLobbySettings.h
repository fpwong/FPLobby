// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FPLobbySettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class FPLOBBY_API UFPLobbySettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere)
	FSoftClassPath LoadingScreenWidget;

	UPROPERTY(config, EditAnywhere)
	FName LobbyMapName = "LobbyMap";

	UPROPERTY(config, EditAnywhere)
	FString GameMapName = "GameMap";
};
