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
#include "BDC_ConfigAndDebug_Config.h"
#include "GeneralProjectSettings.h"
#include "MoviePlayerSettings.h"
#include "Engine/UserInterfaceSettings.h"
#include "BDC_ConfigAndDebug_Settings.h"

// =================================================================================================
//~ Getters
// =================================================================================================

void UBDC_ConfigAndDebug_Config::GetProjectName(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectDescription(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->Description;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectID(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectID.ToString();
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectVersion(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->ProjectVersion;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectCompany(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CompanyName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectCompanyDistinguished(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CompanyDistinguishedName;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectHomepage(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->Homepage;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectSupportContact(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->SupportContact;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectCopyright(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->CopyrightNotice;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectLicense(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->LicensingTerms;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectPrivacyPolicy(FText& AsText, FString& AsString)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		AsString = Settings->PrivacyPolicy;
		AsText = FText::FromString(AsString);
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectWindowPreserveAspect(bool& Value)
{
	if (const UUserInterfaceSettings* Settings = GetDefault<UUserInterfaceSettings>())
	{
		Value = Settings->RenderFocusRule == ERenderFocusRule::Always;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectWindowBorderless(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bUseBorderlessWindow;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectWindowStartAsVR(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bStartInVR;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectWindowAllowResize(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bAllowWindowResize;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectWindowAllowClose(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bAllowClose;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectWindowAllowMaximize(bool& Value)
{
	if (const UGeneralProjectSettings* Settings = GetDefault<UGeneralProjectSettings>())
	{
		Value = Settings->bAllowMaximize;
	}
	else
	{
		Value = false;
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectMoviesAreSkippable(bool& Value)
{
	if (const UMoviePlayerSettings* Settings = GetDefault<UMoviePlayerSettings>())
	{
		Value = Settings->bMoviesAreSkippable;
	}
	else
	{
		Value = true;
	}
}

void UBDC_ConfigAndDebug_Config::GetProjectMoviesWaitForCompletion(bool& Value)
{
	if (const UMoviePlayerSettings* Settings = GetDefault<UMoviePlayerSettings>())
	{
		Value = Settings->bWaitForMoviesToComplete;
	}
	else
	{
		Value = true;
	}
}

void UBDC_ConfigAndDebug_Config::GetCurrentPlaySetup(ENum_ProjectSetupOutExec& OutExec, FGameplayTagContainer& StateTags)
{
    if (!IsPlayInEditor()) {
        OutExec = ENum_ProjectSetupOutExec::Exec_Release;
        return;
    }
    
    if (const UBDC_ConfigAndDebug_Settings* Settings = GetDefault<UBDC_ConfigAndDebug_Settings>())
    {
        StateTags = Settings->CurrentPlayStateTags;
        switch(Settings->CurrentPlayState)
        {
            case ENum_ProjectSetupType::Setup_Release:
            {
                OutExec = ENum_ProjectSetupOutExec::Exec_Release;
                break;
            }
            case ENum_ProjectSetupType::Setup_Debug:
            {
                OutExec = ENum_ProjectSetupOutExec::Exec_Debug;
                break;
            }
            case ENum_ProjectSetupType::Setup_DebugNo:
            {
                OutExec = ENum_ProjectSetupOutExec::Exec_Debug;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

// =================================================================================================
//~ Setters
// =================================================================================================

#if WITH_EDITOR

void UBDC_ConfigAndDebug_Config::SetProjectName(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->ProjectName = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectDescription(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->Description = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectID(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		if (FGuid NewGuid; FGuid::ParseExact(FromString, EGuidFormats::DigitsWithHyphens, NewGuid))
		{
			Settings->ProjectID = NewGuid;
		}
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectVersion(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->ProjectVersion = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectCompany(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CompanyName = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectCompanyDistinguished(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CompanyDistinguishedName = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectHomepage(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->Homepage = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectSupportContact(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->SupportContact = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectCopyright(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->CopyrightNotice = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectLicense(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->LicensingTerms = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectPrivacyPolicy(const FString& FromString)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->PrivacyPolicy = FromString;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectWindowPreserveAspect(bool bNewValue)
{
	if (UUserInterfaceSettings* Settings = GetMutableDefault<UUserInterfaceSettings>())
	{
		Settings->RenderFocusRule = bNewValue 
			? ERenderFocusRule::Always 
			: ERenderFocusRule::Never;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectWindowBorderless(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bUseBorderlessWindow = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectWindowStartAsVR(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bStartInVR = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectWindowAllowResize(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowWindowResize = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectWindowAllowClose(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowClose = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectWindowAllowMaximize(const bool bNewValue)
{
	if (UGeneralProjectSettings* Settings = GetMutableDefault<UGeneralProjectSettings>())
	{
		Settings->bAllowMaximize = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectMoviesAreSkippable(const bool bNewValue)
{
	if (UMoviePlayerSettings* Settings = GetMutableDefault<UMoviePlayerSettings>())
	{
		Settings->bMoviesAreSkippable = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

void UBDC_ConfigAndDebug_Config::SetProjectMoviesWaitForCompletion(const bool bNewValue)
{
	if (UMoviePlayerSettings* Settings = GetMutableDefault<UMoviePlayerSettings>())
	{
		Settings->bWaitForMoviesToComplete = bNewValue;
		Settings->TryUpdateDefaultConfigFile();
	}
}

#endif