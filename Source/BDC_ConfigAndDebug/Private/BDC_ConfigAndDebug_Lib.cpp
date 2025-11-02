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
#include "BDC_ConfigAndDebug_Lib.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformApplicationMisc.h"

#if PLATFORM_WINDOWS
	#include "Windows/AllowWindowsPlatformTypes.h"
	#include "Windows/WindowsHWrapper.h"
	#include "Windows/HideWindowsPlatformTypes.h"
	#include <ShellScalingApi.h>
#endif

#if PLATFORM_WINDOWS
namespace BDC_Monitor
{
	struct FMonitorEnumData
	{
		TArray<FMonitorInformations>* MonitorInfoArray;
		int32 CurrentIndex;
		int32 TargetIndex;
		FMonitorInformations* TargetMonitorInfo;
	};
}
#endif

void UBDC_ConfigAndDebug_Lib::DimensionTo1D(const TArray<int32>& ArrayCoords, const TArray<int32>& DimensionSizes, int32& Out1DIndex)
{
	if (ArrayCoords.Num() != DimensionSizes.Num())
	{
		Out1DIndex = -1;
		return;
	}
	int32 ArrayPos = 0;
	int32 Multiplier = 1;
	for (int32 i = 0; i < ArrayCoords.Num(); ++i)
	{
		const int32 Index = ArrayCoords[i];
		const int32 Size = DimensionSizes[i];

		if (Index < 0 || Index >= Size || Size <= 0)
		{
			Out1DIndex = -1;
			return;
		}
		ArrayPos += Index * Multiplier;
		Multiplier *= Size;
	}

	Out1DIndex = ArrayPos;
}

void UBDC_ConfigAndDebug_Lib::Index1DToDimension(int32 ArrayPos, const TArray<int32>& DimensionSizes,  TArray<int32>& OutMultiIndex)
{
	if (ArrayPos < 0 || DimensionSizes.Num() == 0)
	{
		OutMultiIndex = TArray<int32>();
		return;
	}

	TArray<int32> ArrayCoords;
	ArrayCoords.SetNum(DimensionSizes.Num());
	int32 RemainingPos = ArrayPos;
	for (int32 i = 0; i < DimensionSizes.Num(); ++i)
	{
		const int32 Size = DimensionSizes[i];

		if (Size <= 0)
		{
			OutMultiIndex = TArray<int32>();
			return;
		}

		ArrayCoords[i] = RemainingPos % Size;
		RemainingPos /= Size;
	}

	if (RemainingPos != 0)
	{
		OutMultiIndex = TArray<int32>();
		return;
	}

	OutMultiIndex = ArrayCoords;
}

#if PLATFORM_WINDOWS
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC /*hdcMonitor*/, LPRECT /*lprcMonitor*/, LPARAM dwData)
{
    BDC_Monitor::FMonitorEnumData* EnumData = reinterpret_cast<BDC_Monitor::FMonitorEnumData*>(dwData);

    MONITORINFOEXW MonitorInfoEx;
    MonitorInfoEx.cbSize = sizeof(MONITORINFOEXW);

    if (::GetMonitorInfoW(hMonitor, &MonitorInfoEx))
    {
        FMonitorInformations Monitor;
        Monitor.MonitorName = FString(MonitorInfoEx.szDevice);
        Monitor.MonitorResolutionMaxWidth = MonitorInfoEx.rcMonitor.right - MonitorInfoEx.rcMonitor.left;
        Monitor.MonitorResolutionMaxHeight = MonitorInfoEx.rcMonitor.bottom - MonitorInfoEx.rcMonitor.top;
        Monitor.MonitorIndex = EnumData->CurrentIndex;
        if (EnumData->TargetMonitorInfo && EnumData->CurrentIndex == EnumData->TargetIndex)
        {
            *EnumData->TargetMonitorInfo = Monitor;
        }
        if (EnumData->MonitorInfoArray)
        {
            EnumData->MonitorInfoArray->Add(Monitor);
        }

        EnumData->CurrentIndex++;
    }
    return 1;
}

namespace
{
    struct FCaptureIndexData
    {
        int32 Current = 0;
        int32 Target = 0;
        HMONITOR Out = nullptr;
    };

    BOOL CALLBACK MonitorEnumIndexProc(HMONITOR hMonitor, HDC /*hdc*/, LPRECT /*rc*/, LPARAM data)
    {
        FCaptureIndexData* D = reinterpret_cast<FCaptureIndexData*>(data);
        if (D->Current == D->Target)
        {
            D->Out = hMonitor;
            return 0; // stop
        }
        ++D->Current;
        return 1; // continue
    }
}
#endif

FMonitorInformations UBDC_ConfigAndDebug_Lib::GetMonitorInfoByIndex(int32 OfIndex)
{
    FMonitorInformations Result;

#if PLATFORM_WINDOWS
    if (OfIndex < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("GetMonitorInfo: Monitor Index must be non-negative. Index: %d"), OfIndex);
        return Result;
    }

    BDC_Monitor::FMonitorEnumData EnumData;
    EnumData.MonitorInfoArray = nullptr;
    EnumData.CurrentIndex = 0;
    EnumData.TargetIndex = OfIndex;
    EnumData.TargetMonitorInfo = &Result;

    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, (LPARAM)&EnumData);
    
    if (EnumData.CurrentIndex <= OfIndex)
    {
        UE_LOG(LogTemp, Warning, TEXT("GetMonitorInfo: Monitor Index %d not found. Only %d monitors available."), OfIndex, EnumData.CurrentIndex);
        return FMonitorInformations();
    }
#else
    UE_LOG(LogTemp, Warning, TEXT("Monitor functionality is only implemented for Windows (Win64)."));
#endif

    return Result;
}

TArray<FMonitorInformations> UBDC_ConfigAndDebug_Lib::GetAllMonitorInfo()
{
    TArray<FMonitorInformations> ResultArray;

#if PLATFORM_WINDOWS
    BDC_Monitor::FMonitorEnumData EnumData;
    EnumData.MonitorInfoArray = &ResultArray;
    EnumData.CurrentIndex = 0;
    EnumData.TargetIndex = -1;
    EnumData.TargetMonitorInfo = nullptr;

    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&EnumData);

    if (ResultArray.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("GetAllMonitorInfo: Failed to enumerate any monitors."));
    }
#else
    UE_LOG(LogTemp, Warning, TEXT("Monitor functionality is only implemented for Windows (Win64)."));
#endif

    return ResultArray;
}

void UBDC_ConfigAndDebug_Lib::SetSelectedMonitor(int32 NewMonitorIndex)
{
#if PLATFORM_WINDOWS
    if (GIsEditor)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: No effect in Editor. Use Standalone/Packaged."));
        return;
    }
    if (NewMonitorIndex < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: Invalid monitor index %d."), NewMonitorIndex);
        return;
    }

    // Capture HMONITOR by index
    FCaptureIndexData Capture{};
    Capture.Target = NewMonitorIndex;
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumIndexProc, (LPARAM)&Capture);
    if (!Capture.Out)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: Monitor index %d not found."), NewMonitorIndex);
        return;
    }

    MONITORINFOEXW Mi{};
    Mi.cbSize = sizeof(MONITORINFOEXW);
    if (!::GetMonitorInfoW(Capture.Out, &Mi))
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: GetMonitorInfoW failed for index %d."), NewMonitorIndex);
        return;
    }

    TSharedPtr<SWindow> GameWindow = GEngine && GEngine->GameViewport ? GEngine->GameViewport->GetWindow() : nullptr;
    if (!GameWindow.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: Game window not valid."));
        return;
    }

    const int32 NewX = Mi.rcMonitor.left;
    const int32 NewY = Mi.rcMonitor.top;
    HWND hWnd = static_cast<HWND>(GameWindow->GetNativeWindow()->GetOSWindowHandle());
    if (hWnd)
    {
        ::SetWindowPos(hWnd, nullptr, NewX, NewY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
        UE_LOG(LogTemp, Display, TEXT("SetSelectedMonitor: Moved window to monitor %d at (%d,%d)."), NewMonitorIndex, NewX, NewY);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: OS window handle invalid."));
    }
#else
    UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor is only implemented for Windows (Win64)."));
#endif
}