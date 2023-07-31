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

	if (!LobbyItemType)
	{
		UE_LOG(LogTemp, Warning, TEXT("FPUWLobby: Forgot to set lobby item type"));
		return;
	}

	if (AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld()))
	{
		for (TObjectPtr<APlayerState> PlayerState : GameState->PlayerArray)
		{
			if (UFPUWLobbyItem* LobbyItem = WidgetTree->ConstructWidget<UFPUWLobbyItem>(LobbyItemType))
			{
				LobbyItem->SetPlayerState(PlayerState);
				LobbyPanel->AddChild(LobbyItem);
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
