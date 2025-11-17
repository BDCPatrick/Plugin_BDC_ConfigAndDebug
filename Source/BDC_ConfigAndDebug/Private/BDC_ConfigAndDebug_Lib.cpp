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

#include "Framework/Application/SlateApplication.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "GenericPlatform/GenericApplication.h"
#include "GameFramework/GameUserSettings.h"
#include "Widgets/SWindow.h"
#include "Internationalization/Regex.h"

#pragma region MonitorAPI
FMonitorInformations UBDC_ConfigAndDebug_Lib::GetMonitorInfoByIndex(int32 OfIndex)
{
    FMonitorInformations OutInfo;

    FDisplayMetrics DisplayMetrics;
    FSlateApplication::Get().GetDisplayMetrics(DisplayMetrics);

    if (!DisplayMetrics.MonitorInfo.IsValidIndex(OfIndex))
    {
        return OutInfo;
    }

    const FMonitorInfo& Monitor = DisplayMetrics.MonitorInfo[OfIndex];
    const int32 MaxW = Monitor.MaxResolution.X > 0 ? Monitor.MaxResolution.X : Monitor.NativeWidth;
    const int32 MaxH = Monitor.MaxResolution.Y > 0 ? Monitor.MaxResolution.Y : Monitor.NativeHeight;

    OutInfo.MonitorName = Monitor.Name;
    OutInfo.MonitorIndex = OfIndex;
    OutInfo.MonitorResolutionMaxWidth = MaxW;
    OutInfo.MonitorResolutionMaxHeight = MaxH;
    if (MaxW <= 0 || MaxH <= 0)
    {
        OutInfo.MonitorAspectRation = 1.777777777777778f;
    }else
    {
        OutInfo.MonitorAspectRation = static_cast<float>(MaxW) / static_cast<float>(MaxH);
    }

    return OutInfo;
}

TArray<FMonitorInformations> UBDC_ConfigAndDebug_Lib::GetAllMonitorInfo()
{
    TArray<FMonitorInformations> Result;

    FDisplayMetrics DisplayMetrics;
    FSlateApplication::Get().GetDisplayMetrics(DisplayMetrics);

    for (int32 Index = 0; Index < DisplayMetrics.MonitorInfo.Num(); ++Index)
    {
        const FMonitorInfo& Monitor = DisplayMetrics.MonitorInfo[Index];
        const int32 MaxW = Monitor.MaxResolution.X > 0 ? Monitor.MaxResolution.X : Monitor.NativeWidth;
        const int32 MaxH = Monitor.MaxResolution.Y > 0 ? Monitor.MaxResolution.Y : Monitor.NativeHeight;

        FMonitorInformations Info;
        Info.MonitorName = Monitor.Name;
        Info.MonitorIndex = Index;
        Info.MonitorResolutionMaxWidth = MaxW;
        Info.MonitorResolutionMaxHeight = MaxH;
        if (MaxW <= 0 || MaxH <= 0)
        {
            Info.MonitorAspectRation = 1.777777777777778f;
        }else
        {
         Info.MonitorAspectRation = static_cast<float>(MaxW) / static_cast<float>(MaxH);
        }

        Result.Add(Info);
    }

    return Result;
}

void UBDC_ConfigAndDebug_Lib::SetSelectedMonitor(int32 NewMonitorIndex)
{
    FDisplayMetrics DisplayMetrics;
    FSlateApplication::Get().GetDisplayMetrics(DisplayMetrics);
    if (!DisplayMetrics.MonitorInfo.IsValidIndex(NewMonitorIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: Invalid monitor index %d"), NewMonitorIndex);
        return;
    }

    const FMonitorInfo& Target = DisplayMetrics.MonitorInfo[NewMonitorIndex];
    const int32 WindowPosX = Target.WorkArea.Left;
    const int32 WindowPosY = Target.WorkArea.Top;

    TSharedPtr<SWindow> GameWin;
    if (GEngine && GEngine->GameViewport)
    {
        GameWin = GEngine->GameViewport->GetWindow();
    }
    if (!GameWin.IsValid())
    {
        GameWin = FSlateApplication::Get().GetActiveTopLevelWindow();
    }
    if (!GameWin.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("SetSelectedMonitor: Game window not found"));
        return;
    }

    const EWindowMode::Type CurrentWindowMode = GameWin->GetWindowMode();
    GameWin->SetWindowMode(EWindowMode::Windowed);
    GameWin->MoveWindowTo(FVector2D((float)WindowPosX, (float)WindowPosY));
    GameWin->SetWindowMode(CurrentWindowMode);

    UE_LOG(LogTemp, Display, TEXT("SetSelectedMonitor: Switched to monitor %d at (%d,%d)."), NewMonitorIndex, WindowPosX, WindowPosY);
}
#pragma endregion

#pragma region StringSystem
static bool BDC_IsAlpha(const TCHAR C)
{
    return FChar::IsAlpha(C);
}

static bool BDC_IsDigit(const TCHAR C)
{
    return FChar::IsDigit(C);
}

static bool BDC_IsAlnum(const TCHAR C)
{
    return FChar::IsAlpha(C) || FChar::IsDigit(C);
}

static void BDC_ShuffleCharsInIndices(const TArray<int32>& Indices, FString& InOut)
{
    if (Indices.Num() <= 1)
    {
        return;
    }
    TArray<TCHAR> Values;
    Values.Reserve(Indices.Num());
    for (int32 Idx : Indices) { Values.Add(InOut[Idx]); }

    FRandomStream Rng;
    Rng.Initialize((int32)FPlatformTime::Cycles());
    for (int32 i = Values.Num() - 1; i > 0; --i)
    {
        const int32 j = Rng.RandRange(0, i);
        if (i != j)
        {
            Swap(Values[i], Values[j]);
        }
    }
    for (int32 k = 0; k < Indices.Num(); ++k)
    {
        InOut[Indices[k]] = Values[k];
    }
}

void UBDC_ConfigAndDebug_Lib::StringAdvancedCheck(FString Input, ENum_StringCheck CheckupType, FString Substring, bool bUseCaseSensitive, bool bSearchFromEnd, bool& bResult, FString& Output)
{
    Output = Input;
    bResult = false;
    const ESearchCase::Type SearchCase = bUseCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase;

    switch (CheckupType)
    {
        case ENum_StringCheck::StringHasSubstring:
        {
            if (Substring.Len() == 0)
            {
                bResult = true;
            }
            else
            {
                const int32 FoundAt = Input.Find(Substring, SearchCase, bSearchFromEnd ? ESearchDir::FromEnd : ESearchDir::FromStart);
                bResult = FoundAt != INDEX_NONE;
            }
            break;
        }
        case ENum_StringCheck::StringIsNumeric:
        {
            if (Input.Len() == 0) { bResult = false; break; }
            bResult = true;
            for (const TCHAR C : Input) { if (!BDC_IsDigit(C)) { bResult = false; break; } }
            break;
        }
        case ENum_StringCheck::StringIsAlphabetical:
        {
            if (Input.Len() == 0) { bResult = false; break; }
            bResult = true;
            for (const TCHAR C : Input) { if (!BDC_IsAlpha(C)) { bResult = false; break; } }
            break;
        }
        case ENum_StringCheck::StringIsSpecial:
        {
            if (Input.Len() == 0) { bResult = false; break; }
            bResult = true;
            for (const TCHAR C : Input) { if (BDC_IsAlnum(C) || C == TEXT(' ')) { bResult = false; break; } }
            break;
        }
        case ENum_StringCheck::StringIsAlphabeticalNumeric:
        {
            if (Input.Len() == 0) { bResult = false; break; }
            bResult = true;
            for (const TCHAR C : Input) { if (!BDC_IsAlnum(C)) { bResult = false; break; } }
            break;
        }
        case ENum_StringCheck::StringIsAlphabeticalSpecial:
        {
            if (Input.Len() == 0) { bResult = false; break; }
            bResult = true;
            for (const TCHAR C : Input) { if (!(BDC_IsAlpha(C) || (!BDC_IsAlnum(C) && C != TEXT(' ')))) { bResult = false; break; } }
            break;
        }
        case ENum_StringCheck::StringIsNumericSpecial:
        {
            if (Input.Len() == 0) { bResult = false; break; }
            bResult = true;
            for (const TCHAR C : Input) { if (!(BDC_IsDigit(C) || (!BDC_IsAlnum(C) && C != TEXT(' ')))) { bResult = false; break; } }
            break;
        }
        case ENum_StringCheck::StringIsURL:
        {
            const FRegexPattern Pattern(TEXT("^(http?|https?|ftp)://"));
            FRegexMatcher Matcher(Pattern, Input);
            bResult = Matcher.FindNext();
            break;
        }
        case ENum_StringCheck::StringHasNumeric:
        {
            bResult = false; for (const TCHAR C : Input) { if (BDC_IsDigit(C)) { bResult = true; break; } }
            break;
        }
        case ENum_StringCheck::StringHasAlphabetic:
        {
            bResult = false; for (const TCHAR C : Input) { if (BDC_IsAlpha(C)) { bResult = true; break; } }
            break;
        }
        case ENum_StringCheck::StringHasSpecial:
        {
            bResult = false; for (const TCHAR C : Input) { if (!BDC_IsAlnum(C) && C != TEXT(' ')) { bResult = true; break; } }
            break;
        }
        case ENum_StringCheck::StringHasUppercase:
        {
            bResult = false; for (const TCHAR C : Input) { if (FChar::IsUpper(C)) { bResult = true; break; } }
            break;
        }
        case ENum_StringCheck::StringHasLowercase:
        {
            bResult = false; for (const TCHAR C : Input) { if (FChar::IsLower(C)) { bResult = true; break; } }
            break;
        }
    }
}

void UBDC_ConfigAndDebug_Lib::StringAdvancedReplace(FString Input, ENum_StringReplace ReplaceType, FString SearchFor, FString ReplaceWith, bool bUseCaseSensitive, bool bStartFromEnd, int32 SkipCases, FString& Output)
{
    Output = Input;
    if (SearchFor.Len() == 0)
    {
        return;
    }
    if (SkipCases < 0)
    {
        SkipCases = 0;
    }

    const ESearchCase::Type SearchCase = bUseCaseSensitive ? ESearchCase::CaseSensitive : ESearchCase::IgnoreCase;

    auto ReplaceAtIndex = [&](int32 Index)
    {
        if (Index == INDEX_NONE) { return; }
        Output = Output.Left(Index) + ReplaceWith + Output.Mid(Index + SearchFor.Len());
    };

    switch (ReplaceType)
    {
        case ENum_StringReplace::StringRepAll:
        {
            Output = Output.Replace(*SearchFor, *ReplaceWith, SearchCase);
            break;
        }
        case ENum_StringReplace::StringRepOnlyFirst:
        {
            const int32 Index = Output.Find(SearchFor, SearchCase, bStartFromEnd ? ESearchDir::FromEnd : ESearchDir::FromStart);
            ReplaceAtIndex(Index);
            break;
        }
        case ENum_StringReplace::StringRepOnlyLast:
        {
            const int32 Index = Output.Find(SearchFor, SearchCase, ESearchDir::FromEnd);
            ReplaceAtIndex(Index);
            break;
        }
        case ENum_StringReplace::StringRepSkip:
        {
            int32 Count = 0;
            if (!bStartFromEnd)
            {
                int32 Pos = -1;
                while (true)
                {
                    const int32 Next = Output.Find(SearchFor, SearchCase, ESearchDir::FromStart, Pos + 1);
                    if (Next == INDEX_NONE) { break; }
                    if (Count == SkipCases)
                    {
                        ReplaceAtIndex(Next);
                        break;
                    }
                    ++Count;
                    Pos = Next;
                }
            }
            else
            {
                int32 Pos = Output.Len();
                while (true)
                {
                    const int32 Next = Output.Find(SearchFor, SearchCase, ESearchDir::FromEnd, Pos);
                    if (Next == INDEX_NONE) { break; }
                    if (Count == SkipCases)
                    {
                        ReplaceAtIndex(Next);
                        break;
                    }
                    ++Count;
                    Pos = Next - 1;
                }
            }
            break;
        }
    }
}

void UBDC_ConfigAndDebug_Lib::StringReverse(FString Input, ENum_StringSort ReverseType, FString& Output)
{
    Output = Input;
    switch (ReverseType)
    {
        case ENum_StringSort::StringSortFull:
        {
            Output = Input.Reverse();
            break;
        }
        case ENum_StringSort::StringSortSentence:
        {
            FString Result;
            Result.Reserve(Input.Len());
            int32 Start = 0;
            for (int32 i = 0; i < Input.Len(); ++i)
            {
                const TCHAR C = Input[i];
                if (C == TEXT('.') || C == TEXT(';'))
                {
                    const FString Segment = Input.Mid(Start, i - Start);
                    Result += Segment.Reverse();
                    Result.AppendChar(C);
                    Start = i + 1;
                }
            }
            if (Start <= Input.Len() - 1)
            {
                const FString Tail = Input.Mid(Start);
                Result += Tail.Reverse();
            }
            Output = Result;
            break;
        }
        case ENum_StringSort::StringSortWord:
        {
            FString Result;
            Result.Reserve(Input.Len());
            int32 Start = 0;
            for (int32 i = 0; i < Input.Len(); ++i)
            {
                const TCHAR C = Input[i];
                if (C == TEXT(' '))
                {
                    const FString Segment = Input.Mid(Start, i - Start);
                    Result += Segment.Reverse();
                    Result.AppendChar(TEXT(' '));
                    Start = i + 1;
                }
            }
            if (Start <= Input.Len() - 1)
            {
                const FString Tail = Input.Mid(Start);
                Result += Tail.Reverse();
            }
            Output = Result;
            break;
        }
    }
}

void UBDC_ConfigAndDebug_Lib::StringJiggle(FString Input, ENum_StringSort JiggleType, FString& Output)
{
    Output = Input;

    auto JiggleRange = [&](int32 Begin, int32 End)
    {
        if (Begin >= End) { return; }
        TArray<int32> ShufflableIndices;
        for (int32 i = Begin; i < End; ++i)
        {
            const TCHAR C = Output[i];
            if (C == TEXT(' ') || C == TEXT('.') || C == TEXT(';'))
            {
                continue;
            }
            ShufflableIndices.Add(i);
        }
        BDC_ShuffleCharsInIndices(ShufflableIndices, Output);
    };

    switch (JiggleType)
    {
        case ENum_StringSort::StringSortFull:
        {
            JiggleRange(0, Output.Len());
            break;
        }
        case ENum_StringSort::StringSortSentence:
        {
            int32 Start = 0;
            for (int32 i = 0; i < Output.Len(); ++i)
            {
                const TCHAR C = Output[i];
                if (C == TEXT('.') || C == TEXT(';'))
                {
                    JiggleRange(Start, i);
                    Start = i + 1;
                }
            }
            JiggleRange(Start, Output.Len());
            break;
        }
        case ENum_StringSort::StringSortWord:
        {
            int32 Start = 0;
            for (int32 i = 0; i < Output.Len(); ++i)
            {
                const TCHAR C = Output[i];
                if (C == TEXT(' '))
                {
                    JiggleRange(Start, i);
                    Start = i + 1;
                }
            }
            JiggleRange(Start, Output.Len());
            break;
        }
    }
}
#pragma endregion

#pragma region ArrayStuff
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

void UBDC_ConfigAndDebug_Lib::SortStringArray(const TArray<FString>& InArray, E_StringSortingOrder SortingOrder, bool bReverseGlyph, TArray<FString>& OutArray)
{
    OutArray = InArray;

    auto GetSortableString = [bReverseGlyph](const FString& Input) -> FString
    {
        return bReverseGlyph ? Input.Reverse() : Input;
    };

    if (SortingOrder == E_StringSortingOrder::alphabetical)
    {
        OutArray.Sort([&GetSortableString](const FString& A, const FString& B)
        {
            return GetSortableString(A).Compare(GetSortableString(B)) < 0;
        });
    }
    else
    {
        OutArray.Sort([&GetSortableString](const FString& A, const FString& B)
        {
            return GetSortableString(A).Compare(GetSortableString(B)) > 0;
        });
    }
}

void UBDC_ConfigAndDebug_Lib::SortTextArray(const TArray<FText>& InArray, E_StringSortingOrder SortingOrder, bool bReverseGlyph, TArray<FText>& OutArray)
{
    OutArray = InArray;

    if (bReverseGlyph)
    {
        auto GetSortableString = [](const FText& Input) -> FString
        {
            return Input.ToString().Reverse();
        };

        if (SortingOrder == E_StringSortingOrder::alphabetical)
        {
            OutArray.Sort([&GetSortableString](const FText& A, const FText& B)
            {
                return GetSortableString(A).Compare(GetSortableString(B)) < 0;
            });
        }
        else
        {
            OutArray.Sort([&GetSortableString](const FText& A, const FText& B)
            {
                return GetSortableString(A).Compare(GetSortableString(B)) > 0;
            });
        }
    }
    else
    {
        if (SortingOrder == E_StringSortingOrder::alphabetical)
        {
            OutArray.Sort([](const FText& A, const FText& B)
            {
                return A.CompareTo(B) < 0;
            });
        }
        else
        {
            OutArray.Sort([](const FText& A, const FText& B)
            {
                return A.CompareTo(B) > 0;
            });
        }
    }
}

void UBDC_ConfigAndDebug_Lib::SortNameArray(const TArray<FName>& InArray, E_StringSortingOrder SortingOrder, bool bReverseGlyph, TArray<FName>& OutArray)
{
    OutArray = InArray;

    if (bReverseGlyph)
    {
        auto GetSortableString = [](const FName& Input) -> FString
        {
            return Input.ToString().Reverse();
        };

        if (SortingOrder == E_StringSortingOrder::alphabetical)
        {
            OutArray.Sort([&GetSortableString](const FName& A, const FName& B)
            {
                return GetSortableString(A).Compare(GetSortableString(B)) < 0;
            });
        }
        else
        {
            OutArray.Sort([&GetSortableString](const FName& A, const FName& B)
            {
                return GetSortableString(A).Compare(GetSortableString(B)) > 0;
            });
        }
    }
    else
    {
        if (SortingOrder == E_StringSortingOrder::alphabetical)
        {
            OutArray.Sort([](const FName& A, const FName& B)
            {
                return A.Compare(B) < 0;
            });
        }
        else
        {
            OutArray.Sort([](const FName& A, const FName& B)
            {
                return A.Compare(B) > 0;
            });
        }
    }
}

void UBDC_ConfigAndDebug_Lib::SortIntArray(const TArray<int32>& InArray, E_IntSortingOrder SortingOrder, TArray<int32>& OutArray)
{
    OutArray = InArray;

    switch (SortingOrder)
    {
        case E_IntSortingOrder::increment:
            OutArray.Sort([](const int32& A, const int32& B) { return A < B; });
            break;
        case E_IntSortingOrder::decrement:
            OutArray.Sort([](const int32& A, const int32& B) { return A > B; });
            break;
        case E_IntSortingOrder::alphabeticalBlock:
        {
            auto GetSortableString = [](int32 Input) -> FString
            {
                const FString Str = FString::FromInt(Input);
                return Str;
            };
            OutArray.Sort([&GetSortableString](const int32& A, const int32& B)
            {
                return GetSortableString(A).Compare(GetSortableString(B)) < 0;
            });
            break;
        }
    }
}

void UBDC_ConfigAndDebug_Lib::SortInt64Array(const TArray<int64>& InArray, E_IntSortingOrder SortingOrder, TArray<int64>& OutArray)
{
    OutArray = InArray;

    switch (SortingOrder)
    {
        case E_IntSortingOrder::increment:
            OutArray.Sort([](const int64& A, const int64& B) { return A < B; });
            break;
        case E_IntSortingOrder::decrement:
            OutArray.Sort([](const int64& A, const int64& B) { return A > B; });
            break;
        case E_IntSortingOrder::alphabeticalBlock:
        {
            auto GetSortableString = [](int64 Input) -> FString
            {
                const FString Str = FString::FromInt(Input);
                return Str;
            };
            OutArray.Sort([&GetSortableString](const int64& A, const int64& B)
            {
                return GetSortableString(A).Compare(GetSortableString(B)) < 0;
            });
            break;
        }
    }
}

void UBDC_ConfigAndDebug_Lib::SortFloatArray(const TArray<float>& InArray, E_IntSortingOrder SortingOrder, TArray<float>& OutArray)
{
    OutArray = InArray;

    switch (SortingOrder)
    {
        case E_IntSortingOrder::increment:
            OutArray.Sort([](const float& A, const float& B) { return A < B; });
            break;
        case E_IntSortingOrder::decrement:
            OutArray.Sort([](const float& A, const float& B) { return A > B; });
            break;
        case E_IntSortingOrder::alphabeticalBlock:
        {
            auto GetSortableString = [](float Input) -> FString
            {
                const FString Str = FString::SanitizeFloat(Input);
                return Str;
            };
            OutArray.Sort([&GetSortableString](const float& A, const float& B)
            {
                return GetSortableString(A).Compare(GetSortableString(B)) < 0;
            });
            break;
        }
    }
}

void UBDC_ConfigAndDebug_Lib::SortVectorArray(const TArray<FVector>& InArray, E_Vec3SortingOrder SortingOrder, TArray<FVector>& OutArray)
{
    OutArray = InArray;
    switch (SortingOrder)
    {
        case E_Vec3SortingOrder::ByX:
            OutArray.Sort([](const FVector& A, const FVector& B) { return A.X < B.X; });
            break;
        case E_Vec3SortingOrder::ByY:
            OutArray.Sort([](const FVector& A, const FVector& B) { return A.Y < B.Y; });
            break;
        case E_Vec3SortingOrder::ByZ:
            OutArray.Sort([](const FVector& A, const FVector& B) { return A.Z < B.Z; });
            break;
    }
}

void UBDC_ConfigAndDebug_Lib::SortVector2Array(const TArray<FVector2D>& InArray, E_Vec2SortingOrder SortingOrder, TArray<FVector2D>& OutArray)
{
    OutArray = InArray;
    switch (SortingOrder)
    {
        case E_Vec2SortingOrder::ByX:
            OutArray.Sort([](const FVector2D& A, const FVector2D& B) { return A.X < B.X; });
            break;
        case E_Vec2SortingOrder::ByY:
            OutArray.Sort([](const FVector2D& A, const FVector2D& B) { return A.Y < B.Y; });
            break;
    }
}

void UBDC_ConfigAndDebug_Lib::SortVector2fArray(const TArray<FVector2f>& InArray, E_Vec2SortingOrder SortingOrder, TArray<FVector2f>& OutArray)
{
    OutArray = InArray;
    switch (SortingOrder)
    {
        case E_Vec2SortingOrder::ByX:
            OutArray.Sort([](const FVector2f& A, const FVector2f& B) { return A.X < B.X; });
            break;
        case E_Vec2SortingOrder::ByY:
            OutArray.Sort([](const FVector2f& A, const FVector2f& B) { return A.Y < B.Y; });
            break;
    }
}

void UBDC_ConfigAndDebug_Lib::SortVector2iArray(const TArray<FIntVector2>& InArray, E_Vec2SortingOrder SortingOrder, TArray<FIntVector2>& OutArray)
{
    OutArray = InArray;
    switch (SortingOrder)
    {
        case E_Vec2SortingOrder::ByX:
            OutArray.Sort([](const FIntVector2& A, const FIntVector2& B) { return A.X < B.X; });
            break;
        case E_Vec2SortingOrder::ByY:
            OutArray.Sort([](const FIntVector2& A, const FIntVector2& B) { return A.Y < B.Y; });
            break;
    }
}

void UBDC_ConfigAndDebug_Lib::SortIntPointArray(const TArray<FIntPoint>& InArray, E_Vec2SortingOrder SortingOrder, TArray<FIntPoint>& OutArray)
{
    OutArray = InArray;
    switch (SortingOrder)
    {
        case E_Vec2SortingOrder::ByX:
            OutArray.Sort([](const FIntPoint& A, const FIntPoint& B) { return A.X < B.X; });
            break;
        case E_Vec2SortingOrder::ByY:
            OutArray.Sort([](const FIntPoint& A, const FIntPoint& B) { return A.Y < B.Y; });
            break;
    }
}

void UBDC_ConfigAndDebug_Lib::SortVector4Array(const TArray<FVector4>& InArray, E_Vec4SortingOrder SortingOrder, TArray<FVector4>& OutArray)
{
    OutArray = InArray;
    switch (SortingOrder)
    {
        case E_Vec4SortingOrder::ByX:
            OutArray.Sort([](const FVector4& A, const FVector4& B) { return A.X < B.X; });
            break;
        case E_Vec4SortingOrder::ByY:
            OutArray.Sort([](const FVector4& A, const FVector4& B) { return A.Y < B.Y; });
            break;
        case E_Vec4SortingOrder::ByZ:
            OutArray.Sort([](const FVector4& A, const FVector4& B) { return A.Z < B.Z; });
            break;
        case E_Vec4SortingOrder::ByW:
            OutArray.Sort([](const FVector4& A, const FVector4& B) { return A.W < B.W; });
            break;
    }
}

void UBDC_ConfigAndDebug_Lib::SortMarginArray(const TArray<FMargin>& InArray, E_MarginSortingOrder SortingOrder, TArray<FMargin>& OutArray)
{
    OutArray = InArray;
    switch (SortingOrder)
    {
        case E_MarginSortingOrder::ByLeft:
            OutArray.Sort([](const FMargin& A, const FMargin& B) { return A.Left < B.Left; });
            break;
        case E_MarginSortingOrder::ByTop:
            OutArray.Sort([](const FMargin& A, const FMargin& B) { return A.Top < B.Top; });
            break;
        case E_MarginSortingOrder::ByRight:
            OutArray.Sort([](const FMargin& A, const FMargin& B) { return A.Right < B.Right; });
            break;
        case E_MarginSortingOrder::ByBottom:
            OutArray.Sort([](const FMargin& A, const FMargin& B) { return A.Bottom < B.Bottom; });
            break;
    }
}

void UBDC_ConfigAndDebug_Lib::SortResolutionArray(const TArray<FString>& InResolutions, E_ResSortingOrder SortingOrder, TArray<FString>& OutResolutions)
{
    OutResolutions = InResolutions;
    auto GetTotalPixels = [](const FString& ResString) -> int64
    {
        FString ResPart;
        FString SuffixPart;

        if (!ResString.Split(TEXT(" "), &ResPart, &SuffixPart, ESearchCase::IgnoreCase, ESearchDir::FromStart))
        {
            ResPart = ResString;
        }

        FString WidthStr;
        FString HeightStr;

        if (ResPart.Split(TEXT("x"), &WidthStr, &HeightStr, ESearchCase::IgnoreCase, ESearchDir::FromStart))
        {
            const int32 Width = FCString::Atoi(*WidthStr);
            const int32 Height = FCString::Atoi(*HeightStr);
            
            return (int64)Width * (int64)Height; 
        }

        return 0;
    };

    if (SortingOrder == E_ResSortingOrder::LowestToHighest)
    {
        OutResolutions.Sort([&GetTotalPixels](const FString& A, const FString& B)
        {
            return GetTotalPixels(A) < GetTotalPixels(B);
        });
    }
    else
    {
        OutResolutions.Sort([&GetTotalPixels](const FString& A, const FString& B)
        {
            return GetTotalPixels(A) > GetTotalPixels(B);
        });
    }
}
#pragma endregion