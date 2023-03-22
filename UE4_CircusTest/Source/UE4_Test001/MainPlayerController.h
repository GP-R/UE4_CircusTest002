// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	UPROPERTY(VisibleAnywhere, Category = "Widget")
		TSubclassOf<class UMainCharacterWidget> MainLvWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
		TSubclassOf<class UUserWidget> SelectMaskWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UMainCharacterWidget* PlayerUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = true))
		class UUserWidget* SelectMaskUI;
public:
	class UMainCharacterWidget* GetPlayerUI();

	UFUNCTION(BlueprintCallable)
		void HidePlayerUI();

	UFUNCTION(BlueprintCallable)
		void VisiblePlayerUI();
};
