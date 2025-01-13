// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "FPUWServerBrowser.generated.h"

class UCircularThrobber;
class UCommonButtonBase;
class UScrollBox;
class UCommonListView;
class FOnlineSessionSearch;
class UFPUWServerBrowserItem;

UCLASS()
class FPLOBBY_API UFPSearchResultObject : public UObject
{
	GENERATED_BODY()

public:
	FOnlineSessionSearchResult SearchResult;
};

UCLASS()
class FPLOBBY_API UFPUWServerBrowser : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFPUWServerBrowser();

	//~ Begin UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	virtual bool Initialize() override;
	//~ End UUserWidget interface

	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	UFUNCTION()
	void RefreshLobbyList();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFPUWServerBrowserItem> BrowserItemTemplate;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonListView* LobbyList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonButtonBase* RefreshButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCircularThrobber* RefreshThrobber;

	UFUNCTION()
	void OnFindSessionsComplete(bool bSuccess);

	TSharedPtr<FOnlineSessionSearch> SearchObject; 
};
