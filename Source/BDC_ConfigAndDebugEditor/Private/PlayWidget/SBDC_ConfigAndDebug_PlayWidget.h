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
#include "Widgets/SCompoundWidget.h"
#include "BDC_ConfigAndDebug_Types.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SComboButton.h"

class SBDC_ConfigAndDebug_PlayWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SBDC_ConfigAndDebug_PlayWidget) {}
    SLATE_END_ARGS();

    void Construct(const FArguments& InArgs);

private:
    void OnSelectionChanged(TSharedPtr<ENum_ProjectSetupType> NewSelection, ESelectInfo::Type SelectInfo);
    TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<ENum_ProjectSetupType> InItem);
    FText GetCurrentItemLabel() const;
    FText GetEnumAsText(ENum_ProjectSetupType EnumValue) const;
    FText GetCurrentTagsSummary() const;
    TSharedRef<SWidget> CreateTagContainerMenu();
    TArray<TSharedPtr<ENum_ProjectSetupType>> ComboBoxOptions;
    TSharedPtr<SComboBox<TSharedPtr<ENum_ProjectSetupType>>> ComboBox;
    TSharedPtr<SComboButton> TagPickerButton;
};