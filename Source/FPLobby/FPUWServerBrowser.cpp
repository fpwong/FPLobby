// Fill out your copyright notice in the Description page of Project Settings.

#include "FPUWServerBrowser.h"

#include "CommonListView.h"
#include "FPUWServerBrowserItem.h"
#include "Online.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Components/CircularThrobber.h"
#include "Widgets/FPCUWCommonButton.h"

void UFPUWServerBrowser::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFPUWServerBrowser::NativeDestruct()
{
	Super::NativeDestruct();
}

void UFPUWServerBrowser::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("Native on init?"));
}

bool UFPUWServerBrowser::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (!IsDesignTime())
	{
		if (RefreshButton)
		{
			RefreshButton->OnPressed().AddUObject(this, &UFPUWServerBrowser::RefreshLobbyList);
		}

		RefreshThrobber->SetVisibility(ESlateVisibility::Hidden);
	}

	// RefreshLobbyList();

	return true;
}

void UFPUWServerBrowser::RefreshLobbyList()
{
	UE_LOG(LogTemp, Warning, TEXT("Refresh lobby list"));
	if (!LobbyList)
		return;

	if (!BrowserItemTemplate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Browesr item template invalid"));
		return;
	}

	LobbyList->SetListItems(TArray<UFPSearchResultObject*>());

	if (IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GetWorld()))
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(this, &UFPUWServerBrowser::OnFindSessionsComplete));

			SearchObject = MakeShareable(new FOnlineSessionSearch);
			SearchObject->MaxSearchResults = 64;
			SearchObject->bIsLanQuery = false;
			Sessions->FindSessions(0, SearchObject.ToSharedRef());

			// Show throbber
			RefreshThrobber->SetVisibility(ESlateVisibility::HitTestInvisible);
			RefreshButton->SetIsEnabled(false);

			UE_LOG(LogTemp, Warning, TEXT("Finding sessions..."));
		}
	}
}

void UFPUWServerBrowser::OnFindSessionsComplete(bool bSuccess)
{
	RefreshThrobber->SetVisibility(ESlateVisibility::Hidden);
	RefreshButton->SetIsEnabled(true);

	if (bSuccess)
	{
		TArray<UFPSearchResultObject*> SearchResultObjects;
		for (const FOnlineSessionSearchResult& SearchResult : SearchObject->SearchResults)
		{
			UFPSearchResultObject* SearchResultObject = NewObject<UFPSearchResultObject>();
			SearchResultObject->SearchResult = SearchResult;
			SearchResultObjects.Add(SearchResultObject);
		}

		LobbyList->SetListItems(SearchResultObjects);

		UE_LOG(LogTemp, Warning, TEXT("Found sessions! %d"), SearchObject->SearchResults.Num());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find sessions"));
	}
}
