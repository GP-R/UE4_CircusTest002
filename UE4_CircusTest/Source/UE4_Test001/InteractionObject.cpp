// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionObject.h"

// Sets default values
AInteractionObject::AInteractionObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionObject::Interaction_Implementation()
{
}


