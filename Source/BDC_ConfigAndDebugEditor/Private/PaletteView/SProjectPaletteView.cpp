/* Copyright © beginning at 2025 - BlackDevilCreations
* Author: Patrick Wenzel
* All rights reserved.
* This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
* or modified without prior written permission from BlackDevilCreations.
* Unreal Engine and its associated trademarks are property of Epic Games, Inc.
* and are used with permission.
*/
#include "PaletteView/SProjectPaletteView.h"
#include "BDC_ConfigAndDebug_Settings.h"
#include "BDC_ConfigAndDebug_Types.h" 
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SButton.h"
#include "Styling/CoreStyle.h"
#include "Math/Color.h"

#define LOCTEXT_NAMESPACE "SProjectPaletteView"

void SProjectPaletteView::Construct(const FArguments& InArgs)
{
    OnColorSelected = InArgs._OnColorSelected;

    ChildSlot
    [
        BuildPaletteView()
    ];
}

TSharedRef<SWidget> SProjectPaletteView::CreateColorTile(const FLinearColor& Color, const int32 Index)
{
    const FText TooltipText = FText::Format(LOCTEXT("PaletteColorTooltip", "Palette Color {0}: R:{1} G:{2} B:{3} A:{4}"),
        FText::AsNumber(Index),
        FText::AsNumber(Color.R),
        FText::AsNumber(Color.G),
        FText::AsNumber(Color.B),
        FText::AsNumber(Color.A)
    );

    return SNew(SButton)
        .ToolTipText(TooltipText)
        .ButtonStyle(FCoreStyle::Get(), "NoBorder")
        .OnClicked(this, &SProjectPaletteView::OnColorTileClicked, Color)
        .ContentPadding(FMargin(2.0f))
        .ButtonColorAndOpacity(Color.ToFColor(false))
        [
            SNew(SColorBlock)
            .Color(Color)
            .Size(FVector2D(24.0f, 24.0f))
        ];
}

FReply SProjectPaletteView::OnColorTileClicked(const FLinearColor Color)
{
    OnColorSelected.ExecuteIfBound(Color);
    return FReply::Handled();
}

TSharedRef<SWidget> SProjectPaletteView::BuildPaletteView()
{
    const UBDC_ConfigAndDebug_Settings* Settings;
    UBDC_ConfigAndDebug_Settings::GetProjectPaletteSettings(Settings);

    if (!Settings)
    {
        return SNew(STextBlock).Text(LOCTEXT("SettingsError", "Error: BDC_ConfigAndDebug_Settings not found."));
    }

    TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);
    
    {
        TSharedRef<SWrapBox> FreeColorsWrapBox = SNew(SWrapBox).UseHAlignedFlow(true);
        for (const FLinearColor& Color : Settings->FreeProjectColors)
        {
            FreeColorsWrapBox->AddChild(CreateColorTile(Color, Settings->FreeProjectColors.IndexOfByKey(Color)));
        }

        VerticalBox->AddSlot()
        .AutoHeight()
        .Padding(4.0f, 8.0f)
        [
            SNew(SExpandableArea)
            .HeaderPadding(FMargin(0.0f))
            .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
            .InitiallyCollapsed(false)
            .HeaderContent()
            [
                SNew(STextBlock)
                .Text(LOCTEXT("FreeColorsHeader", "Free Project Colors"))
                .Font(FCoreStyle::GetDefault().GetFontStyle("SmallFont"))
            ]
            .BodyContent()
            [
                FreeColorsWrapBox
            ]
        ];
    }
	
    if (Settings->ProjectPalettes.Num() > 0)
    {
        for (const auto& Pair : Settings->ProjectPalettes)
        {
            const FName PaletteName = Pair.Key;
            const FPaletteofColors& Palette = Pair.Value;

            TSharedRef<SWrapBox> PaletteWrapBox = SNew(SWrapBox).UseHAlignedFlow(true);
            for (const FLinearColor& Color : Palette.ColorsOfPalette)
            {
                PaletteWrapBox->AddChild(CreateColorTile(Color, Palette.ColorsOfPalette.IndexOfByKey(Color)));
            }
            
            VerticalBox->AddSlot()
            .AutoHeight()
            .Padding(4.0f, 4.0f)
            [
                SNew(SExpandableArea)
                .HeaderPadding(FMargin(0.0f))
                .BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
                .InitiallyCollapsed(true)
                .HeaderContent()
                [
                    SNew(STextBlock)
                    .Text(FText::FromName(PaletteName))
                    .Font(FCoreStyle::GetDefault().GetFontStyle("SmallFont"))
                ]
                .BodyContent()
                [
                    PaletteWrapBox
                ]
            ];
        }
    }

    return SNew(SScrollBox)
        .Orientation(Orient_Vertical)
        + SScrollBox::Slot()
        [
            VerticalBox
        ];
}

#undef LOCTEXT_NAMESPACE