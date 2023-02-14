// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "MainCharacterWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "InteractionObject.h"
#include "TimerManager.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = -70.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	SpringArm->bUsePawnControlRotation = true;
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance(TEXT("AnimBlueprint'/Game/Blueprints/CPPBlueprints/ABP_MainCharacter.ABP_MainCharacter_C'"));
	if (AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	/*static ConstructorHelpers::FClassFinder<UUserWidget> PUI(TEXT("WidgetBlueprint'/Game/Blueprints/CPPBlueprints/WBP_MainCharacter_2.WBP_MainCharacter_2_C'"));
	if (PUI.Succeeded())
	{
		WidgetClass = PUI.Class;
	}*/

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ScreenAimPos = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
	InteractionRange = 2000.f;
	if (WidgetClass != nullptr)
	{
		PlayerUI = Cast<UMainCharacterWidget>(CreateWidget(GetWorld(), WidgetClass));
		if (PlayerUI != nullptr)
		{
			PlayerUI->GetPressFKey()->SetVisibility(ESlateVisibility::Hidden);
			PlayerUI->AddToViewport();
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector OutWorldLocation;
	FVector OutWorldDirection;
	bool bAim = playerController->DeprojectScreenPositionToWorld(ScreenAimPos.X, ScreenAimPos.Y, OutWorldLocation, OutWorldDirection);
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	if (!bAim)
		return;

	bool bHitResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		OutWorldLocation,
		(OutWorldDirection * InteractionRange) + OutWorldLocation,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params);

	FColor DrawColor;
	if (bHitResult)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;
	DrawDebugLine(
		GetWorld(),
		OutWorldLocation,
		(OutWorldDirection * InteractionRange) + OutWorldLocation,
		DrawColor, false, 1, 0, 0.1);

	if (bHitResult) // 상호작용하는 오브젝트와 에임이 맞았을경우
	{
		//delegate 해서 이벤트로하면 더 효율이 좋을듯
		//hit된 액터 스스로 자기가 맞았다는걸 인식하고 하이라이트
		//F키를 누르면
		//TODO
		//InteractionObject cpp하나 만들어서 가면이나 사다리 블루프린트들이 상속을받음
		//
		InteractionObject = Cast<AInteractionObject>(HitResult.Actor);
		if (InteractionObject)
		{
			InteractionObject->StartHighlight();
			PlayerUI->GetPressFKey()->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (InteractionObject)
		{
			InteractionObject->EndHighlight();
			InteractionObject = nullptr;
			PlayerUI->GetPressFKey()->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}


// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &AMainCharacter::Interaction);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMainCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMainCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::LookUp);

}

//void AMainCharacter::PostInitializeComponents()
//{
//	PlayerUI->InitWidget();
//}

void AMainCharacter::UpDown(float Value)
{
	if (Value == 0.f)
		return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMainCharacter::Interaction()
{
	if (InteractionObject)
	{
		InteractionObject->Interaction();
	}
}
