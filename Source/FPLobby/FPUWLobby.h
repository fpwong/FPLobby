﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Blueprint/UserWidget.h"
#include "CommonButtonBase.h"
#include "Widgets/FPCUWCommonButton.h"
#include "FPUWLobby.generated.h"

class UCommonButtonBase;
class UFPUWLobbyItem;

UCLASS()
class FPLOBBY_API UFPUWLobby : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	virtual void RefreshPlayers();

	UFUNCTION()
	void HandleAddOrRemovePlayerState(APlayerState* PlayerState);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFPUWLobbyItem> LobbyItemType;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* LobbyPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UFPCUWCommonButton* ReadyOrStartButton;

	UFUNCTION()
	void HandleReadyOrStartButtonClicked();
};