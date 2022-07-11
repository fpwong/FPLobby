// Fill out your copyright notice in the Description page of Project Settings.

#include "FPLobbyGameMode.h"

#include "FPLobbyGameState.h"
#include "FPLobbyPlayerController.h"

// Sets default values
AFPLobbyGameMode::AFPLobbyGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerControllerClass = AFPLobbyPlayerController::StaticClass();
	GameStateClass = AFPLobbyGameState::StaticClass();
}
