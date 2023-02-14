// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class UE4_TEST001_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//virtual void PostInitializeComponents() override;
	void UpDown(float Value);
	void LeftRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Interaction();

public:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleAnywhere)
		class UMainCharacterWidget* PlayerUI;

	UPROPERTY(VisibleAnywhere)
		APlayerController* playerController;

	UPROPERTY(VisibleAnywhere)
		FVector2D ScreenAimPos;

	UPROPERTY(VisibleAnywhere)
		float InteractionRange;

	UPROPERTY(VisibleAnywhere)
		class AInteractionObject* InteractionObject;

};
