// Fill out your copyright notice in the Description page of Project Settings.

#include "FPUWServerBrowserItem.h"

#include "FPUWServerBrowser.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "Online.h"
#include "OnlineSubsystemUtils.h"
#include "GameFramework/PlayerState.h"

void UFPUWServerBrowserItem::InitSessionResult(const FOnlineSessionSearchResult& InSearchResult)
{
	SearchResult = InSearchResult;

	// Set lobby name to server name setting, otherwise use the owner's name
	if (auto ServerNameSetting = SearchResult.Session.SessionSettings.Settings.Find(FName("SERVER_NAME")))
	{
		FString ServerName;
		ServerNameSetting->Data.GetValue(ServerName);

		LobbyNameLabel->SetText(FText::FromString(ServerName));
	}
	else
	{
		LobbyNameLabel->SetText(FText::FromString(SearchResult.Session.OwningUserName));
	}

	int32 MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
	int32 CurrentPlayers = MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
	NumPlayersLabel->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentPlayers, MaxPlayers)));

	PingLabel->SetText(FText::FromString(FString::Printf(TEXT("%d ms"), SearchResult.PingInMs)));

	JoinButton->OnClicked().AddUObject(this, &UFPUWServerBrowserItem::OnJoinButtonClicked);
}

void UFPUWServerBrowserItem::OnJoinButtonClicked()
{
	if (IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GetWorld()))
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			if (APlayerState* PlayerState = UGameplayStatics::GetPlayerState(GetWorld(), 0))
			{
				FUniqueNetIdPtr PlayerNetId = PlayerState->GetUniqueId().GetUniqueNetId();
				OnJoinSessionHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(this, &UFPUWServerBrowserItem::OnJoinSessionComplete));
				Sessions->JoinSession(*PlayerNetId, NAME_GameSession, SearchResult);
				UE_LOG(LogTemp, Warning, TEXT("Joining session!"));
			}
		}
	}
}

void UFPUWServerBrowserItem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Joined!"));

	// FOnlineSubsystemBPCallHelper Helper(TEXT("JoinSessionCallback"), WorldContextObject);
	// Helper.QueryIDFromPlayerController(PlayerControllerWeakPtr.Get());


	if (IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GetWorld()))
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionHandle);

			if (Result == EOnJoinSessionCompleteResult::Success)
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

				// Client travel to the server
				FString ConnectString;
				if (PlayerController && Sessions->GetResolvedConnectString(NAME_GameSession, ConnectString))
				{
					UE_LOG(LogTemp, Warning, TEXT("Join session: traveling to %s"), *ConnectString);
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
			}
		}
	}
}

void UFPUWServerBrowserItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (UFPSearchResultObject* SearchResultObject = Cast<UFPSearchResultObject>(ListItemObject))
	{
		InitSessionResult(SearchResultObject->SearchResult);
	}
}
