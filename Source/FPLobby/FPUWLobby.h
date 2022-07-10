// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "FPUWLobby.generated.h"

class UFPUWLobbyItem;

UCLASS()
class FPLOBBY_API UFPUWLobby : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFPUWLobbyItem> BrowserItemTemplate;

};
