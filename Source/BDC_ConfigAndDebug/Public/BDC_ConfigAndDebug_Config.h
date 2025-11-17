/* Copyright © beginning at 2025 - BlackDevilCreations
  * Author: Patrick Wenzel
  * All rights reserved.
  * * This file and the corresponding Definition is part of a BlackDevilCreations project and may not be distributed, copied,
  * or modified without prior written permission from BlackDevilCreations.
  * * Unreal Engine and its associated trademarks are property of Epic Games, Inc.
  * and are used with permission.
*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "BDC_ConfigAndDebug_Types.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BDC_ConfigAndDebug_Config.generated.h"


UCLASS()
class BDC_CONFIGANDDEBUG_API UBDC_ConfigAndDebug_Config : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//~ Begin Getters (Runtime)
	// =================================================================================================

	/** Gets the project's name. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Name", Keywords = "project settings name"))
	static void GetProjectName(FText& AsText, FString& AsString);

	/** Gets the project's description. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Description", Keywords = "project settings description"))
	static void GetProjectDescription(FText& AsText, FString& AsString);

	/** Gets the project's unique ID. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project ID", Keywords = "project settings id"))
	static void GetProjectID(FText& AsText, FString& AsString);

	/** Gets the project's version number. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Version", Keywords = "project settings version"))
	static void GetProjectVersion(FText& AsText, FString& AsString);

	/** Gets the project's company name. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Company", Keywords = "project settings company name"))
	static void GetProjectCompany(FText& AsText, FString& AsString);

	/** Gets the project's company distinguished name. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Company Distinguished Name", Keywords = "project settings company distinguished name"))
	static void GetProjectCompanyDistinguished(FText& AsText, FString& AsString);

	/** Gets the project's homepage URL. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Homepage", Keywords = "project settings homepage url website"))
	static void GetProjectHomepage(FText& AsText, FString& AsString);

	/** Gets the project's support contact information. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Support Contact", Keywords = "project settings support contact email"))
	static void GetProjectSupportContact(FText& AsText, FString& AsString);

	/** Gets the project's copyright notice. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Copyright", Keywords = "project settings copyright notice"))
	static void GetProjectCopyright(FText& AsText, FString& AsString);

	/** Gets the project's licensing terms. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Licensing Terms", Keywords = "project settings license terms"))
	static void GetProjectLicense(FText& AsText, FString& AsString);

	/** Gets the project's privacy policy URL. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters", meta = (DisplayName = "Get Project Privacy Policy", Keywords = "project settings privacy policy url"))
	static void GetProjectPrivacyPolicy(FText& AsText, FString& AsString);

	/** Checks if the game window should preserve its aspect ratio. Based on UI Render Focus Rule. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Window", meta = (DisplayName = "Get Project Window Preserve Aspect Ratio", Keywords = "project settings window aspect ratio"))
	static void GetProjectWindowPreserveAspect(bool& Value);

	/** Checks if the game window should be borderless. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Window", meta = (DisplayName = "Get Project Window Is Borderless", Keywords = "project settings window borderless"))
	static void GetProjectWindowBorderless(bool& Value);

	/** Checks if the project is configured to start in VR. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Window", meta = (DisplayName = "Get Project Window Starts As VR", Keywords = "project settings window vr virtual reality"))
	static void GetProjectWindowStartAsVR(bool& Value);

	/** Checks if the game window can be resized by the user. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Window", meta = (DisplayName = "Get Project Window Allows Resize", Keywords = "project settings window allow resize"))
	static void GetProjectWindowAllowResize(bool& Value);

	/** Checks if the game window has a close button. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Window", meta = (DisplayName = "Get Project Window Allows Close", Keywords = "project settings window allow close"))
	static void GetProjectWindowAllowClose(bool& Value);

	/** Checks if the game window has a maximize button. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Window", meta = (DisplayName = "Get Project Window Allows Maximize", Keywords = "project settings window allow maximize"))
	static void GetProjectWindowAllowMaximize(bool& Value);

	/** Checks if startup movies are skippable. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Movies", meta = (DisplayName = "Get Project Movies Are Skippable", Keywords = "project settings movie skip"))
	static void GetProjectMoviesAreSkippable(bool& Value);

	/** Checks if the game waits for startup movies to complete before continuing. */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug|Getters|Movies", meta = (DisplayName = "Get Project Movies Wait For Completion", Keywords = "project settings movie wait complete"))
	static void GetProjectMoviesWaitForCompletion(bool& Value);

	/** Checks if the game currently runs in the Editor */
	UFUNCTION(BlueprintPure, Category = "BDC|Config And Debug", meta = (DisplayName = "Is playing in Editor", Keywords = "Is playing in Editor"))
	static bool IsPlayInEditor()
	{
		return (GWorld != nullptr) && GWorld->IsPlayInEditor();
	};
	
	UFUNCTION(BlueprintCallable, Category = "BDC|Config and Debug", meta = (DisplayName = "Get Play-Setup", Keywords = "Play Setup", ExpandEnumAsExecs = "OutExec"))
	static void GetCurrentPlaySetup(ENum_ProjectSetupOutExec& OutExec, FGameplayTagContainer& StateTags);

	//~ Begin Setters (Editor Only)
	// =================================================================================================

#if WITH_EDITOR

	/** Sets the project's name. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Name", Keywords = "project settings name"))
	static void SetProjectName(const FString& FromString);

	/** Sets the project's description. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Description", Keywords = "project settings description"))
	static void SetProjectDescription(const FString& FromString);

	/** Sets the project's unique ID. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project ID", Keywords = "project settings id"))
	static void SetProjectID(const FString& FromString);

	/** Sets the project's version number. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Version", Keywords = "project settings version"))
	static void SetProjectVersion(const FString& FromString);

	/** Sets the project's company name. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Company", Keywords = "project settings company name"))
	static void SetProjectCompany(const FString& FromString);

	/** Sets the project's company distinguished name. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Company Distinguished Name", Keywords = "project settings company distinguished name"))
	static void SetProjectCompanyDistinguished(const FString& FromString);

	/** Sets the project's homepage URL. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Homepage", Keywords = "project settings homepage url website"))
	static void SetProjectHomepage(const FString& FromString);

	/** Sets the project's support contact information. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Support Contact", Keywords = "project settings support contact email"))
	static void SetProjectSupportContact(const FString& FromString);

	/** Sets the project's copyright notice. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Copyright", Keywords = "project settings copyright notice"))
	static void SetProjectCopyright(const FString& FromString);

	/** Sets the project's licensing terms. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Licensing Terms", Keywords = "project settings license terms"))
	static void SetProjectLicense(const FString& FromString);

	/** Sets the project's privacy policy URL. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters", meta = (DisplayName = "Set Project Privacy Policy", Keywords = "project settings privacy policy url"))
	static void SetProjectPrivacyPolicy(const FString& FromString);

	/** Sets whether the game window should preserve its aspect ratio. Modifies UI Render Focus Rule. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Window", meta = (DisplayName = "Set Project Window Preserve Aspect Ratio", Keywords = "project settings window aspect ratio"))
	static void SetProjectWindowPreserveAspect(bool bNewValue);

	/** Sets whether the game window should be borderless. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Window", meta = (DisplayName = "Set Project Window Is Borderless", Keywords = "project settings window borderless"))
	static void SetProjectWindowBorderless(bool bNewValue);
	
	/** Sets whether the project is configured to start in VR. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Window", meta = (DisplayName = "Set Project Window Starts As VR", Keywords = "project settings window vr virtual reality"))
	static void SetProjectWindowStartAsVR(bool bNewValue);

	/** Sets whether the game window can be resized by the user. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Window", meta = (DisplayName = "Set Project Window Allows Resize", Keywords = "project settings window allow resize"))
	static void SetProjectWindowAllowResize(bool bNewValue);

	/** Sets whether the game window has a close button. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Window", meta = (DisplayName = "Set Project Window Allows Close", Keywords = "project settings window allow close"))
	static void SetProjectWindowAllowClose(bool bNewValue);

	/** Sets whether the game window has a maximize button. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Window", meta = (DisplayName = "Set Project Window Allows Maximize", Keywords = "project settings window allow maximize"))
	static void SetProjectWindowAllowMaximize(bool bNewValue);

	/** Sets whether startup movies are skippable. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Movies", meta = (DisplayName = "Set Project Movies Are Skippable", Keywords = "project settings movie skip"))
	static void SetProjectMoviesAreSkippable(bool bNewValue);
	
	/** Sets whether the game waits for startup movies to complete. (Editor Only) */
	UFUNCTION(BlueprintCallable, Category = "BDC|Config And Debug|Setters|Movies", meta = (DisplayName = "Set Project Movies Wait For Completion", Keywords = "project settings movie wait complete"))
	static void SetProjectMoviesWaitForCompletion(bool bNewValue);
#endif 
};