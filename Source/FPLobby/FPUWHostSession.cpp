// Fill out your copyright notice in the Description page of Project Settings.

#include "FPUWHostSession.h"

#include "CommonButtonBase.h"
#include "FPLobbySettings.h"
#include "Online.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Blueprint/WidgetTree.h"
#include "Components/EditableText.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"

void UFPUWHostSession::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HostButton->OnClicked().AddUObject(this, &UFPUWHostSession::HandleHostButtonClicked);
}

void UFPUWHostSession::NativeConstruct()
{
	Super::NativeConstruct();

	// HostButton->OnClicked().AddUObject(this, &UFPUWHostSession::HandleHostButtonClicked);
}

void UFPUWHostSession::HandleHostButtonClicked()
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Trying to host");
	if (IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GetWorld()))
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			if (APlayerState* PlayerState = UGameplayStatics::GetPlayerState(GetWorld(), 0))
			{
				FUniqueNetIdPtr PlayerNetId = PlayerState->GetUniqueId().GetUniqueNetId();

				const auto CreateSessionDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UFPUWHostSession::OnCreateSessionCompleted);
				CreateCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegate);
				FOnlineSessionSettings SessionSettings;
				SessionSettings.NumPublicConnections = 10;
				SessionSettings.bShouldAdvertise = true;
				SessionSettings.bAllowJoinInProgress = true;
				SessionSettings.bIsLANMatch = false;
				SessionSettings.bAllowInvites = true;
				SessionSettings.bIsDedicated = false;
				SessionSettings.bUsesPresence = true;
				SessionSettings.bAllowJoinViaPresence = true;
				SessionSettings.bUseLobbiesIfAvailable = true;

				FOnlineSessionSetting ServerNameSetting;
				ServerNameSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
				ServerNameSetting.Data = ServerNameField->GetText().ToString();
				SessionSettings.Settings.Add(FName("SERVER_NAME"), ServerNameSetting);

				if (Sessions->CreateSession(*PlayerNetId, NAME_GameSession, SessionSettings))
				{
					UKismetSystemLibrary::PrintString(GetWorld(), "\tCreated session");
				}
				else
				{
					UKismetSystemLibrary::PrintString(GetWorld(), "\tFailed to create session");
				}
			}
		}
	}
	// auto Sessions = Helper.OnlineSub->GetSessionInterface();
	// if (Sessions.IsValid())
	// {
	// 	CreateCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(CreateCompleteDelegate);
	// 		
	// 	FOnlineSessionSettings Settings;
	// }
}

void UFPUWHostSession::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Create session");
	if (IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GetWorld()))
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnCreateSessionCompleteDelegate_Handle(StartCompleteDelegateHandle);

			if (bWasSuccessful)
			{
				const auto StartCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UFPUWHostSession::OnStartSessionCompleted);
				StartCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle(StartCompleteDelegate);
				Sessions->StartSession(NAME_GameSession);
			}
		}
	}
}

void UFPUWHostSession::OnStartSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Start session");
	// UE_LOG(LogTemp, Warning, TEXT("Start session complete %d"), bWasSuccessful);

	if (IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GetWorld()))
	{
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate_Handle(StartCompleteDelegateHandle);

			UGameplayStatics::OpenLevel(GetWorld(), GetDefault<UFPLobbySettings>()->LobbyMapName, true, FString("listen"));
		}
	}
}
