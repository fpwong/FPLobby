// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void SetPlayerState(TObjectPtr<APlayerState> InPlayerState);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* PlayerNameLabel;
};
