// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "FPUWServerBrowserItem.generated.h"

class UButton;
class UTextBlock;
class UCommonListView;

/**
 * 
 */
UCLASS()
class FPLOBBY_API UFPUWServerBrowserItem
	: public UUserWidget
	, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* LobbyNameLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* NumPlayersLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PingLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonButtonBase* JoinButton;

	FOnlineSessionSearchResult SearchResult;

	void InitSessionResult(const FOnlineSessionSearchResult& InSearchResult);

	UFUNCTION()
	void OnJoinButtonClicked();

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

protected:
	// IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// IUserObjectListEntry

private:
	FDelegateHandle OnJoinSessionHandle;
};
