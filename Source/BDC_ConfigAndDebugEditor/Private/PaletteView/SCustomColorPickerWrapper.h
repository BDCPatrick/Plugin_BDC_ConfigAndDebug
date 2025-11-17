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

struct FColorPickerArgs;

class SCustomColorPickerWrapper : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCustomColorPickerWrapper) {}
    SLATE_ARGUMENT(TSharedPtr<FColorPickerArgs>, ColorPickerArgs)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    void OnPaletteColorSelected(FLinearColor SelectedColor);
    TSharedPtr<SWidget> StandardColorPickerWidget;
    TSharedPtr<FColorPickerArgs> Args;
};