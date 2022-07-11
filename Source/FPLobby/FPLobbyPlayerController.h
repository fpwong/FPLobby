﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPLobbyPlayerController.generated.h"

UCLASS()
class FPLOBBY_API AFPLobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPLobbyPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoadingScreenClass;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	virtual void DisplayLoadingScreen();
};
