// Copyright Epic Games, Inc. All Rights Reserved.

#include "SelfguidedMissilesGameMode.h"
#include "SelfguidedMissilesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASelfguidedMissilesGameMode::ASelfguidedMissilesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
