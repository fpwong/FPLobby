// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPLobbyGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FFPOnAddOrRemovePlayerState, APlayerState*);

UCLASS()
class FPLOBBY_API AFPLobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPLobbyGameState();

	FFPOnAddOrRemovePlayerState OnAddPlayerState;
	FFPOnAddOrRemovePlayerState OnRemovePlayerState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
};
