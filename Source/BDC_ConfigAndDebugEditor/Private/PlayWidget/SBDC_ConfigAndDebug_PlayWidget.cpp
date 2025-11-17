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
#include "SBDC_ConfigAndDebug_PlayWidget.h"
#include "BDC_ConfigAndDebug_Settings.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Text/STextBlock.h"

void SBDC_ConfigAndDebug_PlayWidget::Construct(const FArguments& InArgs)
{
    UEnum* Enum = StaticEnum<ENum_ProjectSetupType>();
    for (int32 i = 0; i < Enum->NumEnums() - 1; ++i)
    {
        ComboBoxOptions.Add(MakeShared<ENum_ProjectSetupType>(static_cast<ENum_ProjectSetupType>(Enum->GetValueByIndex(i))));
    }

    ChildSlot
    [
        SNew(SHorizontalBox)
		
        + SHorizontalBox::Slot()
        .AutoWidth()
        .VAlign(VAlign_Center)
        .Padding(4, 0)
        [
            SNew(STextBlock)
            .Text(FText::FromString(TEXT("Mode:")))
        ]
		
        + SHorizontalBox::Slot()
        .AutoWidth()
        .VAlign(VAlign_Center)
        [
			+ SNew(SVerticalBox)
			
			+ SVerticalBox::Slot()
			.Autoheight()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				// TODO: GameplayTagContainer Selector, storing selected tags in UBDC_ConfigAndDebug_Settings > CurrentPlayStateTags
			]
			
			+ SVerticalBox::Slot()
			.Autoheight()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ComboBox, SComboBox<TSharedPtr<ENum_ProjectSetupType>>)
				.OptionsSource(&ComboBoxOptions)
				.OnSelectionChanged(this, &SBDC_ConfigAndDebug_PlayWidget::OnSelectionChanged)
				.OnGenerateWidget(this, &SBDC_ConfigAndDebug_PlayWidget::OnGenerateWidget)
				.Content()
				[
					SNew(STextBlock)
					.Text(this, &SBDC_ConfigAndDebug_PlayWidget::GetCurrentItemLabel)
				]
			]
        ]
    ];
}

void SBDC_ConfigAndDebug_PlayWidget::OnSelectionChanged(TSharedPtr<ENum_ProjectSetupType> NewSelection, ESelectInfo::Type SelectInfo)
{
    if (NewSelection.IsValid())
    {
        if (UBDC_ConfigAndDebug_Settings* Settings = GetMutableDefault<UBDC_ConfigAndDebug_Settings>())
        {
            Settings->CurrentPlayState = *NewSelection;
            Settings->SaveToProjectDefaultConfig();
        }
    }
}

TSharedRef<SWidget> SBDC_ConfigAndDebug_PlayWidget::OnGenerateWidget(TSharedPtr<ENum_ProjectSetupType> InItem)
{
    return SNew(STextBlock).Text(GetEnumAsText(*InItem));
}

FText SBDC_ConfigAndDebug_PlayWidget::GetCurrentItemLabel() const
{
    if (const UBDC_ConfigAndDebug_Settings* Settings = GetDefault<UBDC_ConfigAndDebug_Settings>())
    {
        return GetEnumAsText(Settings->CurrentPlayState);
    }
    return FText::GetEmpty();
}

FText SBDC_ConfigAndDebug_PlayWidget::GetEnumAsText(ENum_ProjectSetupType EnumValue) const
{
    const UEnum* Enum = StaticEnum<ENum_ProjectSetupType>();
    if (Enum)
    {
        return Enum->GetDisplayNameTextByValue(static_cast<int64>(EnumValue));
    }
    return FText::GetEmpty();
}