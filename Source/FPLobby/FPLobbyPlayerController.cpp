// Fill out your copyright notice in the Description page of Project Settings.

#include "FPLobbyPlayerController.h"

// Sets default values
AFPLobbyPlayerController::AFPLobbyPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
}

// Called when the game starts or when spawned
void AFPLobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPLobbyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

