// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Blueprint/UserWidget.h"
#include "CommonButtonBase.h"
#include "FPUWHostSession.generated.h"

class UEditableText;
class UCommonButtonBase;
class UFPUWHostSessionItem;

UCLASS()
class FPLOBBY_API UFPUWHostSession : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFPUWHostSession();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonButtonBase* HostButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableText* ServerNameField;

	FDelegateHandle CreateCompleteDelegateHandle;
	FDelegateHandle StartCompleteDelegateHandle;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	UFUNCTION()
	void HandleHostButtonClicked();

	UFUNCTION()
	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);

	UFUNCTION()
	void OnStartSessionCompleted(FName SessionName, bool bWasSuccessful);
};