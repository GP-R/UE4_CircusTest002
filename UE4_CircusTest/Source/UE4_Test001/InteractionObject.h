// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionObject.generated.h"

UCLASS()
class UE4_TEST001_API AInteractionObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartHighlight();

	UFUNCTION(BlueprintImplementableEvent)
	void EndHighlight();

	UFUNCTION(BlueprintNativeEvent)
	void Interaction();
	virtual void Interaction_Implementation();

};
