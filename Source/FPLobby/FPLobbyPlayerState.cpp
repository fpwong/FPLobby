// Fill out your copyright notice in the Description page of Project Settings.

#include "FPLobbyPlayerState.h"

// Sets default values
AFPLobbyPlayerState::AFPLobbyPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFPLobbyPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();

	OnPlayerNameChanged.Broadcast(GetPlayerName());
}