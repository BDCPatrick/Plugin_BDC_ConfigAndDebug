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
#include "GameplayTagsEditorModule.h"

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
			SNew(SHorizontalBox)

		#pragma region Mode_UI

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(2, 0, 8, 0)
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
		#pragma endregion
		#pragma region Tags_UI
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(8, 0, 2, 0)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("Tags:")))
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0, 0, 2, 0)
				.VAlign(VAlign_Center)
				[
					SAssignNew(TagPickerButton, SComboButton)
					.OnGetMenuContent(this, &SBDC_ConfigAndDebug_PlayWidget::CreateTagContainerMenu)
					.ContentPadding(FMargin(8, 2))
					.ButtonContent()
					[
						SNew(STextBlock).Text(this, &SBDC_ConfigAndDebug_PlayWidget::GetCurrentTagsSummary)
					]
				]
			]
		#pragma endregion
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
	if (const UEnum* Enum = StaticEnum<ENum_ProjectSetupType>())
	{
		return Enum->GetDisplayNameTextByValue(static_cast<int64>(EnumValue));
	}
	return FText::GetEmpty();
}

FText SBDC_ConfigAndDebug_PlayWidget::GetCurrentTagsSummary() const
{
	const UBDC_ConfigAndDebug_Settings* Settings = GetDefault<UBDC_ConfigAndDebug_Settings>();
	if (!Settings)
	{
		return FText::FromString(TEXT("None"));
	}

	const FGameplayTagContainer& Tags = Settings->CurrentPlayStateTags;
	if (Tags.IsEmpty())
	{
		return FText::FromString(TEXT("None"));
	}

	FString Summary;
	bool bFirst = true;
	for (const FGameplayTag& GameplayTagItem : Tags)
	{
		if (!bFirst)
		{
			Summary += TEXT(", ");
		}
		bFirst = false;
		Summary += GameplayTagItem.ToString();
	}
	return FText::FromString(Summary);
}

TSharedRef<SWidget> SBDC_ConfigAndDebug_PlayWidget::CreateTagContainerMenu()
{
	const FGameplayTagContainer Current = (GetDefault<UBDC_ConfigAndDebug_Settings>() ? GetDefault<UBDC_ConfigAndDebug_Settings>()->CurrentPlayStateTags : FGameplayTagContainer());

	TSharedPtr<FGameplayTagContainer> Container = MakeShared<FGameplayTagContainer>();
	*Container = Current;

	return IGameplayTagsEditorModule::Get().MakeGameplayTagContainerWidget(
		FOnSetGameplayTagContainer::CreateLambda([this](const FGameplayTagContainer& NewTags)
		{
			if (UBDC_ConfigAndDebug_Settings* Settings = GetMutableDefault<UBDC_ConfigAndDebug_Settings>())
			{
				Settings->CurrentPlayStateTags = NewTags;
				Settings->SaveToProjectDefaultConfig();
			}
			if (TagPickerButton.IsValid())
			{
				TagPickerButton->SetIsOpen(false);
			}
		}),
		Container
	);
}
