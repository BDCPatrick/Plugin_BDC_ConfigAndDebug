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
#include "Async/Future.h"

class SScrollBox;
class SVerticalBox;

struct FCallableActor
{
	TWeakObjectPtr<AActor> Actor;
	TArray<UFunction*> Functions;
};

class SBDC_ConfigAndDebug_OverlayWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SBDC_ConfigAndDebug_OverlayWidget) {}
    SLATE_END_ARGS()
    void Construct(const FArguments& InArgs);
	void RefreshActorList();

private:
	FReply OnRefreshClicked();
	FReply OnFunctionButtonClicked(TWeakObjectPtr<AActor> Actor, UFunction* Function);
	void PopulateList(const TArray<FCallableActor>& CallableActors);
	TSharedPtr<SScrollBox> ActorListScrollBox;
	TFuture<void> RefreshTaskFuture;
};