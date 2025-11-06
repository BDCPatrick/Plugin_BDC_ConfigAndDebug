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
    /** Sorts from A to Z */
    alphabetical        UMETA(DisplayName = "Alphabetical (A-Z)"),
    /** Sorts from Z to A */
    alphabetical_reversed UMETA(DisplayName = "Alphabetical Reversed (Z-A)")
};

UENUM(BlueprintType)
enum class E_IntSortingOrder : uint8
{
    /** Sorts from smallest to largest (e.g., 1, 2, 10) */
    increment           UMETA(DisplayName = "Incrementing (Smallest to Largest)"),
    /** Sorts from largest to smallest (e.g., 10, 2, 1) */
    decrement           UMETA(DisplayName = "Decrementing (Largest to Smallest)"),
    /** Sorts alphabetically based on the string representation (e.g., 1, 10, 11, 2, 20) */
    alphabeticalBlock   UMETA(DisplayName = "Alphabetical (String Sort)")
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
    /** Sorts from lowest pixel count to highest (e.g., 640x480 -> 1920x1080) */
    LowestToHighest   UMETA(DisplayName = "Lowest to Highest"),
    /** Sorts from highest pixel count to lowest (e.g., 1920x1080 -> 640x480) */
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