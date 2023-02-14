// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Components/WidgetComponent.h"
#include "MainCharacterWidget.h"

AMainPlayerController::AMainPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PUI(TEXT("WidgetBlueprint'/Game/Blueprints/CPPBlueprints/WBP_MainCharacter_2.WBP_MainCharacter_2_C'"));
	if (PUI.Succeeded())
	{
		WidgetClass = PUI.Class;
	}

}

void AMainPlayerController::BeginPlay()
{
	if (WidgetClass != nullptr)
	{
		PlayerUI = Cast<UMainCharacterWidget>(CreateWidget(this, WidgetClass));
		if (PlayerUI != nullptr)
		{
			PlayerUI->GetPressFKey()->SetVisibility(ESlateVisibility::Hidden);
			PlayerUI->AddToViewport();
		}
	}
}

UMainCharacterWidget* AMainPlayerController::GetPlayerUI()
{
	return PlayerUI;
}
