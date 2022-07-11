#include "FPUWLobbyItem.h"

#include "CommonTextBlock.h"
#include "FPLobbyPlayerState.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"

void UFPUWLobbyItem::HandlePlayerKicked()
{
	if (AGameModeBase* GameMode = GetWorld()->GetAuthGameMode())
	{
		if (GameMode->GameSession)
		{
			GameMode->GameSession->KickPlayer(PlayerState->GetPlayerController(), FText::FromString("Kicked from lobby"));
		}
	}
}

void UFPUWLobbyItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(KickButton);
}

void UFPUWLobbyItem::SetPlayerState(TObjectPtr<APlayerState> InPlayerState)
{
	PlayerState = InPlayerState;

	if (AFPLobbyPlayerState* LobbyPlayerState = Cast<AFPLobbyPlayerState>(InPlayerState))
	{
		LobbyPlayerState->OnPlayerNameChanged.AddUObject(this, &UFPUWLobbyItem::HandlePlayerNameChanged);
	}

	if (PlayerNameLabel && InPlayerState)
	{
		FString PlayerName = InPlayerState->GetPlayerName();

		PlayerNameLabel->SetText(FText::FromString(PlayerName.IsEmpty() ? "Unnamed" : PlayerName));
	}

	// set kick button visibility
	ESlateVisibility KickVisibility = ESlateVisibility::Collapsed;

	if (APlayerController* Owner = GetOwningPlayer())
	{
		if (Owner->GetLocalRole() == ROLE_Authority)
		{
			if (PlayerState != GetWorld()->GetFirstPlayerController()->PlayerState)
			{
				KickVisibility = ESlateVisibility::Visible;
				KickButton->OnClicked().AddUObject(this, &UFPUWLobbyItem::HandlePlayerKicked);
			}
		}
	}

	KickButton->SetVisibility(KickVisibility);
}

void UFPUWLobbyItem::HandlePlayerNameChanged(const FString& PlayerName)
{
	if (PlayerNameLabel)
	{
		PlayerNameLabel->SetText(FText::FromString(PlayerName));
	}
}

