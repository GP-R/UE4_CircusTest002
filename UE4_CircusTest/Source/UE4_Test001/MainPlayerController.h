// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterWidget.h"
#include "Components/WidgetComponent.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_TEST001_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

		AMainPlayerController();
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UMainCharacterWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UMainCharacterWidget* PlayerUI;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> SelectUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UUserWidget* SelectShacoUI;
public:
	UMainCharacterWidget* GetPlayerUI();

	UFUNCTION(BlueprintCallable)
		void HidePlayerUI();

	UFUNCTION(BlueprintCallable)
		void VisiblePlayerUI();
};
