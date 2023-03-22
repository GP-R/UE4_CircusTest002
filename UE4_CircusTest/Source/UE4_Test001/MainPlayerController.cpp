// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MainCharacterWidget.h"
#include "Blueprint/UserWidget.h"

AMainPlayerController::AMainPlayerController()
{
	static ConstructorHelpers::FClassFinder<UMainCharacterWidget> PUI(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_MainLv.WBP_MainLv_C'"));

	if (PUI.Succeeded())
	{
		MainLvWidgetClass = PUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SMUI(TEXT("WidgetBlueprint'/Game/Blueprints/Widget/WBP_SelectMask.WBP_SelectMask_C'"));
	if (SMUI.Succeeded())
	{
		SelectMaskWidgetClass = SMUI.Class;

	}
	
}

void AMainPlayerController::BeginPlay()
{
	if (MainLvWidgetClass != nullptr)
	{
		PlayerUI = Cast<UMainCharacterWidget>(CreateWidget(this, MainLvWidgetClass));
		if (PlayerUI != nullptr)
		{
			PlayerUI->GetPressFKey()->SetVisibility(ESlateVisibility::Hidden);
			PlayerUI->AddToViewport();

		}
	}
	if (SelectMaskWidgetClass != nullptr)
	{
		SelectMaskUI = Cast<UUserWidget>(CreateWidget(this, SelectMaskWidgetClass));
		if (SelectMaskUI != nullptr)
		{
			SelectMaskUI->SetVisibility(ESlateVisibility::Hidden);
			SelectMaskUI->AddToViewport();
		}
	}
}

UMainCharacterWidget* AMainPlayerController::GetPlayerUI()
{
	return PlayerUI;
}

void AMainPlayerController::HidePlayerUI()
{
	PlayerUI->SetVisibility(ESlateVisibility::Hidden);
}

void AMainPlayerController::VisiblePlayerUI()
{
	PlayerUI->SetVisibility(ESlateVisibility::Visible);
}