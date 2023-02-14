// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4_Test001GameModeBase.h"
#include "MainCharacter.h"
#include "MainPlayerController.h"

AUE4_Test001GameModeBase::AUE4_Test001GameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
}
