/* Copyright © beginning at 2025 - BlackDevilCreations
* Author: Patrick Wenzel
  * All rights reserved.
  * This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
  * or modified without prior written permission from BlackDevilCreations.
  * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
  * and are used with permission.
*/
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BDC_ConfigAndDebug_Types.h"
#include "BDC_ConfigAndDebug_Lib.generated.h"

UCLASS()
class BDC_CONFIGANDDEBUG_API UBDC_ConfigAndDebug_Lib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#pragma region MonitorAPI
    UFUNCTION(BlueprintPure, Category="BDC|ConfigAndDebug|Monitor Utility", meta=(DisplayName="Get Monitor Info By Index"))
    static FMonitorInformations GetMonitorInfoByIndex(int32 OfIndex); 

    UFUNCTION(BlueprintPure, Category="BDC|ConfigAndDebug|Monitor Utility", meta=(DisplayName="Get All Monitor Infos"))
    static TArray<FMonitorInformations> GetAllMonitorInfo();

    UFUNCTION(BlueprintCallable, Category="BDC|ConfigAndDebug|Monitor Utility", meta=(DisplayName="Set Selected Monitor"))
    static void SetSelectedMonitor(int32 NewMonitorIndex);

    UFUNCTION(BlueprintPure, Category = "BDC|ConfigAndDebug|Monitor Utility", meta=(DisplayName="Get Supported Resolutions"))
    static TArray<FString> GetSupportedResolutions(FIntPoint MinResolution, FIntPoint MaxResolution, float AspectRatio, E_ResType IncludeResolutionsOf);
#pragma endregion
#pragma region ArrayAPI
	UFUNCTION(BlueprintPure, Category = "BDC|ConfigAndDebug|Array Utilitiy", meta = (DisplayName = "Dimension To 1D Index", CompactNodeTitle = "DimTo1D"))
	static void DimensionTo1D(const TArray<int32>& ArrayCoords, const TArray<int32>& DimensionSizes, int32& Out1DIndex);
	
	UFUNCTION(BlueprintPure, Category = "BDC|ConfigAndDebug|Array Utilitiy", meta = (DisplayName = "1D Index To Dimension", CompactNodeTitle = "1DToDim"))
	static void Index1DToDimension(int32 ArrayPos, const TArray<int32>& DimensionSizes,  TArray<int32>& OutMultiIndex);
	
	/** Sorts an array of FString. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|String", meta = (Keywords = "sort array string order"))
    static void SortStringArray(const TArray<FString>& InArray, E_StringSortingOrder SortingOrder, bool bReverseGlyph, UPARAM(DisplayName="Sorted Array") TArray<FString>& OutArray);

    /** Sorts an array of FText. bReverseGlyph is not localization-safe as it converts to FString. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|String", meta = (Keywords = "sort array text order"))
    static void SortTextArray(const TArray<FText>& InArray, E_StringSortingOrder SortingOrder, bool bReverseGlyph, UPARAM(DisplayName="Sorted Array") TArray<FText>& OutArray);

    /** Sorts an array of FName. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|String", meta = (Keywords = "sort array name order"))
    static void SortNameArray(const TArray<FName>& InArray, E_StringSortingOrder SortingOrder, bool bReverseGlyph, UPARAM(DisplayName="Sorted Array") TArray<FName>& OutArray);

    /** Sorts an array of int32. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Numeric", meta = (Keywords = "sort array int integer order"))
    static void SortIntArray(const TArray<int32>& InArray, E_IntSortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<int32>& OutArray);

    /** Sorts an array of int64. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Numeric", meta = (Keywords = "sort array int64 integer order"))
    static void SortInt64Array(const TArray<int64>& InArray, E_IntSortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<int64>& OutArray);

    /** Sorts an array of float. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Numeric", meta = (Keywords = "sort array float order"))
    static void SortFloatArray(const TArray<float>& InArray, E_IntSortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<float>& OutArray);

    /** Sorts an array of FVector (Vector 3D). */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Vector", meta = (Keywords = "sort array vector vector3 order"))
    static void SortVectorArray(const TArray<FVector>& InArray, E_Vec3SortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FVector>& OutArray);

    /** Sorts an array of FVector2D. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Vector", meta = (Keywords = "sort array vector2d order"))
    static void SortVector2Array(const TArray<FVector2D>& InArray, E_Vec2SortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FVector2D>& OutArray);

    /** Sorts an array of FVector2f (float). */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Vector", meta = (Keywords = "sort array vector2f order"))
    static void SortVector2fArray(const TArray<FVector2f>& InArray, E_Vec2SortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FVector2f>& OutArray);

    /** Sorts an array of FVector2i (int32). */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Vector", meta = (Keywords = "sort array vector2i order"))
    static void SortVector2iArray(const TArray<FIntVector2>& InArray, E_Vec2SortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FIntVector2>& OutArray);

    /** Sorts an array of FIntPoint. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Vector", meta = (Keywords = "sort array intpoint order"))
    static void SortIntPointArray(const TArray<FIntPoint>& InArray, E_Vec2SortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FIntPoint>& OutArray);

    /** Sorts an array of FVector4. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Vector", meta = (Keywords = "sort array vector4 order"))
    static void SortVector4Array(const TArray<FVector4>& InArray, E_Vec4SortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FVector4>& OutArray);

    /** Sorts an array of FMargin. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|UI", meta = (Keywords = "sort array margin order"))
    static void SortMarginArray(const TArray<FMargin>& InArray, E_MarginSortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FMargin>& OutArray);

    /** Sorts an array of resolution strings (e.g., "1920x1080 f") by pixel area, ignoring modifiers. */
    UFUNCTION(BlueprintPure, Category = "SortingUtility|Resolution", meta = (Keywords = "sort array resolution graphics settings"))
    static void SortResolutionArray(const TArray<FString>& InResolutions, E_ResSortingOrder SortingOrder, UPARAM(DisplayName="Sorted Array") TArray<FString>& OutResolutions);
#pragma endregion
#pragma region StringSystem
    UFUNCTION(BlueprintPure, Category = "StringSystem", meta=(DisplayName="String Advanced Check"))
    static void StringAdvancedCheck(FString Input, ENum_StringCheck CheckupType, FString Substring, bool bUseCaseSensitive, bool bSearchFromEnd, bool& bResult, FString& Output);

    UFUNCTION(BlueprintPure, Category = "StringSystem", meta=(DisplayName="String Advanced Replace"))
    static void StringAdvancedReplace(FString Input, ENum_StringReplace ReplaceType, FString SearchFor, FString ReplaceWith, bool bUseCaseSensitive, bool bStartFromEnd, int32 SkipCases, FString& Output);

    UFUNCTION(BlueprintPure, Category = "StringSystem", meta=(DisplayName="String Reverse"))
    static void StringReverse(FString Input, ENum_StringSort ReverseType, FString& Output);

    UFUNCTION(BlueprintPure, Category = "StringSystem", meta=(DisplayName="String Jiggle"))
    static void StringJiggle(FString Input, ENum_StringSort JiggleType, FString& Output);
#pragma endregion
};
