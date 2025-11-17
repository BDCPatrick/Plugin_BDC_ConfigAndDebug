/* Copyright © beginning at 2025 - BlackDevilCreations
* Author: Patrick Wenzel
* All rights reserved.
* This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
* or modified without prior written permission from BlackDevilCreations.
* Unreal Engine and its associated trademarks are property of Epic Games, Inc.
* and are used with permission.
*/
#include "PaletteView/SCustomColorPickerWrapper.h"
#include "PaletteView/SProjectPaletteView.h"
#include "ColorPicker/SColorPicker.h"
#include "ColorPicker/ColorPickerManager.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Styling/CoreStyle.h"

#define LOCTEXT_NAMESPACE "SCustomColorPickerWrapper"

void SCustomColorPickerWrapper::Construct(const FArguments& InArgs)
{
    Args = InArgs._ColorPickerArgs;
    
    IColorPickerManagerModule& ColorPickerModule = FModuleManager::LoadModuleChecked<IColorPickerManagerModule>("ColorPicker");
    StandardColorPickerWidget = ColorPickerModule.CreateColorPicker(Args.ToSharedRef());
    
    ChildSlot
    [
        SNew(SHorizontalBox)
        
        + SHorizontalBox::Slot()
        .AutoWidth()
        .Padding(FMargin(0.0f, 0.0f, 8.0f, 0.0f))
        [
            SNew(SBox)
            .MinDesiredWidth(200.0f)
            .MaxDesiredWidth(300.0f)
            [
                SNew(SBorder)
                .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
                [
                    SNew(SProjectPaletteView)
                    .OnColorSelected(this, &SCustomColorPickerWrapper::OnPaletteColorSelected)
                ]
            ]
        ]
		
        + SHorizontalBox::Slot()
        .FillWidth()
        [
            StandardColorPickerWidget.ToSharedRef()
        ]
    ];
}

void SCustomColorPickerWrapper::OnPaletteColorSelected(FLinearColor SelectedColor)
{
    if (Args.IsValid())
    {
        Args->OnColorCommitted.ExecuteIfBound(SelectedColor);
        if (StandardColorPickerWidget.IsValid())
        {
            TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(StandardColorPickerWidget.ToSharedRef());
            if (ParentWindow.IsValid())
            {
                ParentWindow->RequestDestroyWindow();
            }
        }
    }
}

#undef LOCTEXT_NAMESPACE