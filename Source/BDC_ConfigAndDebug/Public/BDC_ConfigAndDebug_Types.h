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
#include "BDC_ConfigAndDebug_Types.generated.h"

UENUM(BlueprintType)
 enum class ENum_ProjectSetupType : uint8
 {
	 Setup_Release UMETA(DisplayName="Release Play"),
	 Setup_Debug UMETA(DisplayName="Debug Play"),
	 Setup_DebugNo UMETA(DisplayName="Debug No Overlay")
 };
 
 UENUM(BlueprintType)
 enum class ENum_ProjectSetupOutExec : uint8
 {
	 Exec_Release UMETA(DisplayName="Release"),
	 Exec_Debug UMETA(DisplayName="Debug")
 };

USTRUCT(BlueprintType)
struct FMonitorInformations
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BDC|ConfigAndDebug|Monitor Utility")
	FString MonitorName = FString("");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BDC|ConfigAndDebug|Monitor Utility")
	int32 MonitorIndex = 0; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BDC|ConfigAndDebug|Monitor Utility")
	int32 MonitorResolutionMaxWidth = 0; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BDC|ConfigAndDebug|Monitor Utility")
	int32 MonitorResolutionMaxHeight = 0;
};