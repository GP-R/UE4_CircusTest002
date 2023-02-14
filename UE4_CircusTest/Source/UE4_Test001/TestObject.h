// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionObject.h"
#include "TestObject.generated.h"

/**
 * 
 */
UCLASS()
class UE4_TEST001_API ATestObject : public AInteractionObject
{
	GENERATED_BODY()
	
public:
	virtual void Interaction_Implementation() override;
};
