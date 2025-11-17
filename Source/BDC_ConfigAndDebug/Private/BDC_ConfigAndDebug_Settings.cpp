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
#include "BDC_ConfigAndDebug_Settings.h"
#include "Engine/World.h"
#include "InputCoreTypes.h"

void UBDC_ConfigAndDebug_Settings::SaveToProjectDefaultConfig()
{
	TryUpdateDefaultConfigFile();
}

UBDC_ConfigAndDebug_Settings::UBDC_ConfigAndDebug_Settings()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("BDC Config and Debug");
	
	CurrentPlayStateTags = FGameplayTagContainer();
	CurrentPlayState = ENum_ProjectSetupType::Setup_Debug;
	OverlayHotkey = EKeys::Three;
}