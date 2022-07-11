// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPLobbyGameMode.generated.h"

UCLASS()
class FPLOBBY_API AFPLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPLobbyGameMode();

	virtual void StartToLeaveMap() override;
};
