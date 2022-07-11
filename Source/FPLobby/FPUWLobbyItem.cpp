#include "FPUWLobbyItem.h"

#include "CommonTextBlock.h"
#include "FPLobbyPlayerState.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"

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
}

void UFPUWLobbyItem::HandlePlayerNameChanged(const FString& PlayerName)
{
	if (PlayerNameLabel)
	{
		PlayerNameLabel->SetText(FText::FromString(PlayerName));
	}
}

