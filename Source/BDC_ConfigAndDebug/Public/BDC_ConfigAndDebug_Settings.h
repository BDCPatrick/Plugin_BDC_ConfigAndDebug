/* Copyright © beginning at 2025 - BlackDevilCreations
  * Author: Patrick Wenzel
  * All rights reserved.
  * 
  * This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
  * or modified without prior written permission from BlackDevilCreations.
  * 
  * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
  * and are used with permission.
*/
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputCoreTypes.h"
#include "Engine/DeveloperSettings.h"
#include "BDC_ConfigAndDebug_Types.h"
#include "BDC_ConfigAndDebug_Settings.generated.h"

UCLASS(Config=Editor, DefaultConfig)
class BDC_CONFIGANDDEBUG_API UBDC_ConfigAndDebug_Settings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBDC_ConfigAndDebug_Settings();

	UPROPERTY(Config, EditAnywhere, Category = "Game Play Mode")
	ENum_ProjectSetupType CurrentPlayState;

	UPROPERTY(Config, EditAnywhere, Category = "Game Play Mode")
	FGameplayTagContainer CurrentPlayStateTags;
	
	UPROPERTY(Config, EditAnywhere, Category = "Debug Overlay")
	FKey OverlayHotkey;

	void SaveToProjectDefaultConfig();
};