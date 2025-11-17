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
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Delegates/Delegate.h"

DECLARE_DELEGATE_OneParam(FOnPaletteColorSelected, FLinearColor);

class SProjectPaletteView : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SProjectPaletteView) {}

    SLATE_EVENT(FOnPaletteColorSelected, OnColorSelected)

    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedRef<SWidget> BuildPaletteView();
    TSharedRef<SWidget> CreateColorTile(const FLinearColor& Color, const int32 Index);
    FReply OnColorTileClicked(const FLinearColor Color);
    FOnPaletteColorSelected OnColorSelected;
};