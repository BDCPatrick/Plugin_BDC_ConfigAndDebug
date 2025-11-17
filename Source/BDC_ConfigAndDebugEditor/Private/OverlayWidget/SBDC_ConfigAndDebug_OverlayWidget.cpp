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
#include "SBDC_ConfigAndDebug_OverlayWidget.h"
#include "BDC_ConfigAndDebug_Settings.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EngineUtils.h"
#include "Editor.h"
#include "Async/Async.h"
#include "UObject/Script.h"
#include "UObject/ScriptMacros.h"

void SBDC_ConfigAndDebug_OverlayWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBox)
		.MaxDesiredWidth(320.0f)
		.MaxDesiredHeight(640.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			.BorderBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.31f))
			.Padding(4.0f)
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(2.0f)
				[
					SNew(SButton)
					.OnClicked(this, &SBDC_ConfigAndDebug_OverlayWidget::OnRefreshClicked)
					.HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("Refresh")))
					]
				]

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SAssignNew(ActorListScrollBox, SScrollBox)
				]
			]
		]
	];
}

void SBDC_ConfigAndDebug_OverlayWidget::RefreshActorList()
{
	if (RefreshTaskFuture.IsValid() && !RefreshTaskFuture.IsReady())
	{
		return;
	}

	ActorListScrollBox->ClearChildren();
	ActorListScrollBox->AddSlot()
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("Refreshing...")))
	];

	RefreshTaskFuture = Async(EAsyncExecution::TaskGraphMainThread, [this]()
	{
		TArray<FCallableActor> CallableActors;
		UWorld* World = nullptr;
		if (GEditor)
		{
			if (GEditor->PlayWorld)
			{
				World = GEditor->PlayWorld.Get();
			}
			else
			{
				World = GEditor->GetEditorWorldContext().World();
			}
		}
		if (World)
		{
			for (AActor* Actor : TActorRange<AActor>(World))
			{
				if (!Actor || Actor->IsActorBeingDestroyed()) continue;

				FCallableActor CallableActor;
				CallableActor.Actor = Actor;

				for (TFieldIterator<UFunction> FuncIt(Actor->GetClass()); FuncIt; ++FuncIt)
				{
					const bool bCallable = FuncIt->HasMetaData(FName(TEXT("CallInEditor"))) || FuncIt->HasAnyFunctionFlags(EFunctionFlags::FUNC_Exec);
					if (bCallable)
					{
						CallableActor.Functions.Add(*FuncIt);
					}
				}

				if (CallableActor.Functions.Num() > 0)
				{
					CallableActors.Add(CallableActor);
				}
			}
		}

		PopulateList(CallableActors);
	});
}

void SBDC_ConfigAndDebug_OverlayWidget::PopulateList(const TArray<FCallableActor>& CallableActors)
{
	ActorListScrollBox->ClearChildren();

	for (const auto& ActorData : CallableActors)
	{
		if (!ActorData.Actor.IsValid()) continue;

		TSharedRef<SVerticalBox> FunctionListBox = SNew(SVerticalBox);
		for (UFunction* Function : ActorData.Functions)
		{
			if (!Function) continue;

			FunctionListBox->AddSlot()
			               .AutoHeight()
			               .Padding(0, 1)
			[
				SNew(SButton)
				.OnClicked(this, &SBDC_ConfigAndDebug_OverlayWidget::OnFunctionButtonClicked, ActorData.Actor, Function)
				.ContentPadding(FMargin(4, 2))
				[
					SNew(STextBlock)
					.Text(FText::FromString(Function->GetName()))
				]
			];
		}

		ActorListScrollBox->AddSlot()
		                  .Padding(2, 4)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryTop"))
				.BorderBackgroundColor(FLinearColor(0.25f, 0.25f, 0.25f, 1.0f))
				.Padding(FMargin(4.0f, 2.0f, 4.0f, 2.0f))
				[
					SNew(STextBlock)
					.Text(FText::FromString(ActorData.Actor->GetActorLabel()))
					.Font(FAppStyle::GetFontStyle("BoldFont"))
				]
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
				.BorderBackgroundColor(FLinearColor(0.13f, 0.13f, 0.13f, 1.0f))
				.Padding(FMargin(8.0f, 0.0f, 4.0f, 4.0f))
				[
					FunctionListBox
				]
			]
		];
	}
}

FReply SBDC_ConfigAndDebug_OverlayWidget::OnRefreshClicked()
{
	RefreshActorList();
	return FReply::Handled();
}

FReply SBDC_ConfigAndDebug_OverlayWidget::OnFunctionButtonClicked(TWeakObjectPtr<AActor> Actor, UFunction* Function)
{
	if (Actor.IsValid() && Function)
	{
		Actor->ProcessEvent(Function, nullptr);
	}
	return FReply::Handled();
}
