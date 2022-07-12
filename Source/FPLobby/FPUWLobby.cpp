// Fill out your copyright notice in the Description page of Project Settings.

#include "FPUWLobby.h"

#include "CommonButtonBase.h"
#include "FPLobbyGameState.h"
#include "FPLobbyPlayerController.h"
#include "FPLobbySettings.h"
#include "FPUWLobbyItem.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"

bool UFPUWLobby::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	//
	// if (!IsDesignTime())
	// {
	// 	RefreshPlayers();
	// 	if (AFPLobbyGameState* LobbyGameState = Cast<AFPLobbyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	// 	{
	// 		LobbyGameState->OnPlayerLogin.AddUObject(this, &UFPUWLobby::HandlePlayerLogin);
	// 	}
	// }

	return true;
}

void UFPUWLobby::NativeConstruct()
{
	RefreshPlayers();

	if (AFPLobbyGameState* LobbyGameState = Cast<AFPLobbyGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		LobbyGameState->OnAddPlayerState.AddUObject(this, &UFPUWLobby::HandleAddOrRemovePlayerState);
		LobbyGameState->OnRemovePlayerState.AddUObject(this, &UFPUWLobby::HandleAddOrRemovePlayerState);
	}

	if (APlayerController* Owner = GetOwningPlayer())
	{
		if (Owner->GetLocalRole() == ROLE_Authority)
		{
			ReadyOrStartButton->ButtonLabel->SetText(FText::FromString("Start"));
		}
		else
		{
			ReadyOrStartButton->ButtonLabel->SetText(FText::FromString("Ready"));
		}
	}

	if (ReadyOrStartButton)
	{
		ReadyOrStartButton->OnClicked().AddUObject(this, &UFPUWLobby::HandleReadyOrStartButtonClicked);
	}
}

void UFPUWLobby::BeginDestroy()
{
	Super::BeginDestroy();
}

void UFPUWLobby::RefreshPlayers()
{
	if (!LobbyPanel)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Refresh players!"));

	LobbyPanel->ClearChildren();

	if (AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld()))
	{
		for (TObjectPtr<APlayerState> PlayerState : GameState->PlayerArray)
		{
			// CreateWidget<>();
			// ;
			// if (UFPUWLobbyItem* LobbyItem = NewObject<UFPUWLobbyItem>(LobbyItemType))
			if (UFPUWLobbyItem* LobbyItem = WidgetTree->ConstructWidget<UFPUWLobbyItem>(LobbyItemType))
			{
				LobbyItem->SetPlayerState(PlayerState);
				LobbyPanel->AddChild(LobbyItem);
				UE_LOG(LogTemp, Warning, TEXT("Added item!"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("LobbyItemTemplate invalid"));
			}
		}
	}
}

void UFPUWLobby::HandleAddOrRemovePlayerState(APlayerState* PlayerState)
{
	RefreshPlayers();
}

void UFPUWLobby::HandleReadyOrStartButtonClicked()
{
	if (APlayerController* Owner = GetOwningPlayer())
	{
		if (Owner->GetLocalRole() == ROLE_Authority)
		{
			GetWorld()->ServerTravel(GetDefault<UFPLobbySettings>()->GameMapName);
		}
		else
		{
			// TODO: ready up logic
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("owner invalid"));
	}
}
