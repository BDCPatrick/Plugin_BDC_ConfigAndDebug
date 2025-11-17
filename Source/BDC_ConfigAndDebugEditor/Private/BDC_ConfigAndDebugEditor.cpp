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
#include "BDC_ConfigAndDebugEditor.h"
#include "BDC_ConfigAndDebug_Settings.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "PlayWidget/SBDC_ConfigAndDebug_PlayWidget.h"
#include "OverlayWidget/SBDC_ConfigAndDebug_OverlayWidget.h"
#include "Framework/Commands/Commands.h"
#include "Framework/Commands/UICommandInfo.h"
#include "Widgets/Docking/SDockTab.h"
#include "Editor/EditorEngine.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Widgets/SWeakWidget.h"
#include "InputCoreTypes.h"
#include "Framework/Commands/InputBindingManager.h"
#include "Framework/Application/IInputProcessor.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SOverlay.h"
#include "ColorPicker/ColorPickerManager.h"
#include "ColorPicker/SColorPicker.h"
#include "PaletteView/SCustomColorPickerWrapper.h"

#define LOCTEXT_NAMESPACE "FBDC_ConfigAndDebugEditorModule"

#pragma region PluginCommands
class FOverlayCommands : public TCommands<FOverlayCommands>
{
public:
	FOverlayCommands(): TCommands<FOverlayCommands>(TEXT("BDC_ConfigAndDebug"), NSLOCTEXT("Contexts", "BDC_ConfigAndDebug", "BDC Config and Debug"), NAME_None, "EditorStyle")
	{
	}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(ToggleOverlay, "Toggle Overlay", "Toggles the actor/function overlay.", EUserInterfaceActionType::Button, FInputChord());
	}

	TSharedPtr<FUICommandInfo> ToggleOverlay;
};
#pragma endregion PluginCommands

#pragma region InputProcessor
class FOverlayInputProcessor : public IInputProcessor
{
public:
	explicit FOverlayInputProcessor(FBDC_ConfigAndDebugEditorModule* const InModule, const FKey InKey)
		: ModulePtr(InModule), OverlayKey(InKey)
	{
	}

	virtual ~FOverlayInputProcessor() override = default;

	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override {}

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override
	{
		if (InKeyEvent.GetKey() == OverlayKey)
		{
			if (ModulePtr)
			{
				ModulePtr->ToggleOverlay();
				return true;
			}
		}
		return false;
	}

private:
	FBDC_ConfigAndDebugEditorModule* ModulePtr = nullptr;
	FKey OverlayKey;
};
#pragma endregion InputProcessor

#pragma region ColorPickerPaletteOverrides
void FBDC_ConfigAndDebugEditorModule::CreateCustomColorPicker(TSharedRef<SWidget>& ReturnedWidget, const TSharedRef<FColorPickerArgs>& Args)
{
    ReturnedWidget = SNew(SCustomColorPickerWrapper)
        .ColorPickerArgs(Args);
}
#pragma endregion ColorPickerPaletteOverrides

#pragma region ModuleLifecycle
void FBDC_ConfigAndDebugEditorModule::StartupModule()
{
	FOverlayCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	const UBDC_ConfigAndDebug_Settings* Settings;
    UBDC_ConfigAndDebug_Settings::GetProjectPaletteSettings(Settings);

	OverlayKey = Settings ? Settings->OverlayHotkey : EKeys::Three;

	PluginCommands->MapAction(
		FOverlayCommands::Get().ToggleOverlay,
		FExecuteAction::CreateRaw(this, &FBDC_ConfigAndDebugEditorModule::ToggleOverlay)
	);

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetGlobalLevelEditorActions()->Append(PluginCommands.ToSharedRef());

	OverlayInputProcessor = MakeShared<FOverlayInputProcessor>(this, OverlayKey);
	FSlateApplication::Get().RegisterInputPreProcessor(OverlayInputProcessor.ToSharedRef());

    FToolMenuOwnerScoped OwnerScoped(this);
    UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
    FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Play");
    Section.AddEntry(FToolMenuEntry::InitWidget("ConfigAndDebugPlayWidget", SNew(SBDC_ConfigAndDebug_PlayWidget), FText::GetEmpty(), true));

	OverlayWidget = SNew(SBDC_ConfigAndDebug_OverlayWidget);
    
    if (FModuleManager::Get().IsModuleLoaded("ColorPicker"))
    {
        IColorPickerManagerModule& ColorPickerModule = FModuleManager::LoadModuleChecked<IColorPickerManagerModule>("ColorPicker");
        
        CustomColorPickerCreationHandle = ColorPickerModule.OnCreateColorPicker()
            .AddRaw(this, &FBDC_ConfigAndDebugEditorModule::CreateCustomColorPicker);
    }
}

void FBDC_ConfigAndDebugEditorModule::ShutdownModule()
{
    if (FModuleManager::Get().IsModuleLoaded("ColorPicker"))
    {
        IColorPickerManagerModule& ColorPickerModule = FModuleManager::GetModuleChecked<IColorPickerManagerModule>("ColorPicker");
        ColorPickerModule.OnCreateColorPicker().Remove(CustomColorPickerCreationHandle);
    }
	if (OverlayInputProcessor.IsValid())
	{
		if (FSlateApplication::IsInitialized())
		{
			FSlateApplication::Get().UnregisterInputPreProcessor(OverlayInputProcessor.ToSharedRef());
		}
		OverlayInputProcessor.Reset();
	}

	const bool bCanRemoveOverlay = bOverlayVisible && (GEngine != nullptr) && (GEngine->GameViewport != nullptr) && OverlayContainer.IsValid();
	if (bCanRemoveOverlay)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(OverlayContainer.ToSharedRef());
		OverlayContainer.Reset();
		bOverlayVisible = false;
	}

	UToolMenus::UnregisterOwner(this);
	FOverlayCommands::Unregister();
}
#pragma endregion ModuleLifecycle

#pragma region Utility
void FBDC_ConfigAndDebugEditorModule::ToggleOverlay()
{
	if (const UBDC_ConfigAndDebug_Settings* Settings; UBDC_ConfigAndDebug_Settings::GetProjectPaletteSettings(Settings))
	{
		if (Settings->CurrentPlayState != ENum_ProjectSetupType::Setup_Debug)
		{
			return;
		}
	}

	if (!OverlayWidget.IsValid() || !GEngine || !GEngine->GameViewport)
	{
		return;
	}

	if (bOverlayVisible)
	{
		if (OverlayContainer.IsValid())
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(OverlayContainer.ToSharedRef());
			OverlayContainer.Reset();
		}
		bOverlayVisible = false;
	}
	else
	{
		SAssignNew(OverlayContainer, SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Top)
		.Padding(FMargin(10.0f))
		[
			SNew(SWeakWidget)
			.PossiblyNullContent(OverlayWidget)
		];

		GEngine->GameViewport->AddViewportWidgetContent(OverlayContainer.ToSharedRef());
		bOverlayVisible = true;
		OverlayWidget->RefreshActorList();
	}
}
#pragma endregion Utility

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBDC_ConfigAndDebugEditorModule, BDC_ConfigAndDebugEditor);