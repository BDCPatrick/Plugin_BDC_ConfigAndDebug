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
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BDC_ConfigAndDebug_Types.h"
#include "BDC_ConfigAndDebug_Lib.generated.h"

UCLASS()
class BDC_CONFIGANDDEBUG_API UBDC_ConfigAndDebug_Lib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	#pragma region ArrayAPI
	UFUNCTION(BlueprintPure, Category = "BDC|ConfigAndDebug|Array Utilitiy", meta = (DisplayName = "Dimension To 1D Index (BDC)", CompactNodeTitle = "DimTo1D"))
	static void DimensionTo1D(const TArray<int32>& ArrayCoords, const TArray<int32>& DimensionSizes, int32& Out1DIndex);
	
	UFUNCTION(BlueprintPure, Category = "BDC|ConfigAndDebug|Array Utilitiy", meta = (DisplayName = "1D Index To Dimension (BDC)", CompactNodeTitle = "1DToDim"))
	static void Index1DToDimension(int32 ArrayPos, const TArray<int32>& DimensionSizes,  TArray<int32>& OutMultiIndex);
	#pragma endregion

#pragma region MonitorAPI
	UFUNCTION(BlueprintPure, Category="BDC|ConfigAndDebug|Monitor Utility", meta=(DisplayName="Get Monitor Info By Index (BDC)"))
	static FMonitorInformations GetMonitorInfoByIndex(int32 OfIndex); 

	UFUNCTION(BlueprintPure, Category="BDC|ConfigAndDebug|Monitor Utility", meta=(DisplayName="Get All Monitor Infos (BDC)"))
	static TArray<FMonitorInformations> GetAllMonitorInfo();

	UFUNCTION(BlueprintCallable, Category="BDC|ConfigAndDebug|Monitor Utility", meta=(DisplayName="Set Selected Monitor (BDC)"))
	static void SetSelectedMonitor(int32 NewMonitorIndex);
#pragma endregion
};
