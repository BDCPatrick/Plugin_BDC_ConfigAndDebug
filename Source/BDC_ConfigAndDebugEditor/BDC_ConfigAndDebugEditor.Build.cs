/* Copyright © beginning at 2025 - BlackDevilCreations
 * Author: Patrick Wenzel
 * All rights reserved.
 * This file is part of a BlackDevilCreations project and may not be distributed, copied,
 * or modified without prior written permission from BlackDevilCreations.
 * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
 * and are used with permission.
 */
using UnrealBuildTool;

public class BDC_ConfigAndDebugEditor : ModuleRules
{
    public BDC_ConfigAndDebugEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Public/BDC_ConfigAndDebugEditor.h";

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Engine",
                "BDC_ConfigAndDebug"
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "DeveloperSettings",
                "MoviePlayer",
                "EngineSettings",
                "LevelEditor",
                "ToolMenus",
                "UnrealEd",
                "InputCore",
                "GameplayTags",
                "GameplayTagsEditor"
            }
        );
    }
}