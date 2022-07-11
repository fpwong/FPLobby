// Fill out your copyright notice in the Description page of Project Settings.

#include "FPLobbyGameState.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AFPLobbyGameState::AFPLobbyGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFPLobbyGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AFPLobbyGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	OnAddPlayerState.Broadcast(PlayerState);
}

void AFPLobbyGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	// Maybe we want to use this somewhere but not now
	if (!GetWorld()->bIsTearingDown)
	{
		OnRemovePlayerState.Broadcast(PlayerState);
	}
}
