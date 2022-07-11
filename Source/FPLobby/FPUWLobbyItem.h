// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Blueprint/UserWidget.h"
#include "FPUWLobbyItem.generated.h"

class UCommonTextBlock;

/**
 * 
 */
UCLASS()
class FPLOBBY_API UFPUWLobbyItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* PlayerNameLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonButtonBase* KickButton;

	virtual void NativeOnInitialized() override;

	void SetPlayerState(TObjectPtr<APlayerState> InPlayerState);

	void HandlePlayerNameChanged(const FString& PlayerName);

	void HandlePlayerKicked();
};
