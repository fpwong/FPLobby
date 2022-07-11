// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FPLobbyPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FFPOnPlayerNameChanged, const FString& NewName)

UCLASS()
class FPLOBBY_API AFPLobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	FFPOnPlayerNameChanged OnPlayerNameChanged;

	// Sets default values for this actor's properties
	AFPLobbyPlayerState();

	virtual void OnRep_PlayerName() override;
};
