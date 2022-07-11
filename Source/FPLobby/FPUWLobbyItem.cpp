#include "FPUWLobbyItem.h"

#include "CommonTextBlock.h"
#include "GameFramework/PlayerState.h"

void UFPUWLobbyItem::SetPlayerState(TObjectPtr<APlayerState> InPlayerState)
{
	if (PlayerNameLabel && InPlayerState)
	{
		PlayerNameLabel->SetText(FText::FromString(InPlayerState->GetPlayerName()));
	}
}