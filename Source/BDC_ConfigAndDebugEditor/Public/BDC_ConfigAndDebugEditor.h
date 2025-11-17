/* Copyright © beginning at 2025 - BlackDevilCreations
 * Author: Patrick Wenzel
 * All rights reserved.
 *
 * This file is part of a BlackDevilCreations project and may not be distributed, copied,
 * or modified without prior written permission from BlackDevilCreations.
 *
 * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
 * and are used with permission.
 */
#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Framework/Commands/UICommandList.h"
class FColorPickerArgs;

class SBDC_ConfigAndDebug_OverlayWidget;
class IInputProcessor;
class SOverlay;
class SCustomColorPickerWrapper;

class FBDC_ConfigAndDebugEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void ToggleOverlay();

private:

	TSharedPtr<SBDC_ConfigAndDebug_OverlayWidget> OverlayWidget;
	TSharedPtr<FUICommandList> PluginCommands;
	bool bOverlayVisible = false;
	FKey OverlayKey;
	TSharedPtr<IInputProcessor> OverlayInputProcessor;
	TSharedPtr<SOverlay> OverlayContainer;
};