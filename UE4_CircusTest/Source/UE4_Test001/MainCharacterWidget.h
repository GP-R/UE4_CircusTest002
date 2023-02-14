// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainCharacterWidget.generated.h"
/**
 *
 */
UCLASS()
class UE4_TEST001_API UMainCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* PressFKey;
public:
	UTextBlock* GetPressFKey();
};
