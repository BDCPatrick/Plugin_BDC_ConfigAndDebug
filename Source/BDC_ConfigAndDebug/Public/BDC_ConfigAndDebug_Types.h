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
 
 UENUM(BlueprintType)
enum class E_StringSortingOrder : uint8
{
    alphabetical	UMETA(DisplayName = "Alphabetical (A-Z)"),
    alphabetical_reversed UMETA(DisplayName = "Alphabetical Reversed (Z-A)")
};

UENUM(BlueprintType)
enum class E_IntSortingOrder : uint8
{
    increment	UMETA(DisplayName = "Incrementing (Smallest to Largest)"),
    decrement	UMETA(DisplayName = "Decrementing (Largest to Smallest)"),
    alphabeticalBlock	UMETA(DisplayName = "Alphabetical (String Sort)")
};

UENUM(BlueprintType)
enum class E_Vec4SortingOrder : uint8
{
    ByX                 UMETA(DisplayName = "Sort by X"),
    ByY                 UMETA(DisplayName = "Sort by Y"),
    ByZ                 UMETA(DisplayName = "Sort by Z"),
    ByW                 UMETA(DisplayName = "Sort by W")
};

UENUM(BlueprintType)
enum class E_Vec3SortingOrder : uint8
{
    ByX                 UMETA(DisplayName = "Sort by X"),
    ByY                 UMETA(DisplayName = "Sort by Y"),
    ByZ                 UMETA(DisplayName = "Sort by Z")
};

UENUM(BlueprintType)
enum class E_Vec2SortingOrder : uint8
{
    ByX                 UMETA(DisplayName = "Sort by X"),
    ByY                 UMETA(DisplayName = "Sort by Y")
};

UENUM(BlueprintType)
enum class E_MarginSortingOrder : uint8
{
    ByLeft              UMETA(DisplayName = "Sort by Left"),
    ByTop               UMETA(DisplayName = "Sort by Top"),
    ByRight             UMETA(DisplayName = "Sort by Right"),
    ByBottom            UMETA(DisplayName = "Sort by Bottom")
};

UENUM(BlueprintType)
enum class E_ResSortingOrder : uint8
{
    LowestToHighest   UMETA(DisplayName = "Lowest to Highest"),
    HighestToLowest   UMETA(DisplayName = "Highest to Lowest")
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