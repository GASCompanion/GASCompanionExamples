// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASCompanionExamples.h"

#include "Editors/LaunchPad/GSCLaunchPadData.h"
#include "Editors/LaunchPad/GSCLaunchPadTypes.h"
#include "Editors/LaunchPad/GSCSampleManager.h"


#define LOCTEXT_NAMESPACE "FGASCompanionExamplesModule"

void FGASCompanionExamplesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Warning, TEXT("FGASCompanionExamplesModule::StartupModule"))

	const TSubclassOf<AGSCSampleManager> SampleAGRManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_AGRPro_SampleManager.BP_AGRPro_SampleManager_C"));
	const TSubclassOf<AGSCSampleManager> SamplePlaygroundManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_Playground_SampleManager.BP_Playground_SampleManager_C"));
	const TSubclassOf<AGSCSampleManager> SampleCustomHUDManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_CustomHUD_SampleManager.BP_CustomHUD_SampleManager_C"));
	const TSubclassOf<AGSCSampleManager> SampleParagonCountessManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_ParagonCountess_SampleManager.BP_ParagonCountess_SampleManager_C"));

	GSCLaunchPadData::RegisteredItems.Empty();

	GSCLaunchPadData::RegisterItem(
		"GAS Companion Playground",
		"",
		"GAS Companion Example map with happy jumping AI and a basic shoot ability to test out the system.\n\nAlso include an example of a DefaultPawn and an Actor with an Ability System Component.",
		"LaunchPad.Card.SamplePlayground",
		{
			FGSCGridItemAction(
				EGSCActionType::OpenSample,
				"/GASCompanionExamples/Examples/Playground/Maps/GASCompanionExampleMap",
				"/GASCompanionExamples/Examples/Playground",
				{},
				SamplePlaygroundManager
			),
			FGSCGridItemAction(EGSCActionType::Documentation,GetDocumentationURL("/quick-start"))
		}
	);

	GSCLaunchPadData::RegisterItem(
		"Custom HUD Example",
		"",
		"This example map demonstrate the use of a custom UI and specific HUD widget. It shows how GAS Companion HUD UserWidget can be used to listen for Gameplay Attributes, Gameplay Tags, and Gameplay Effects changes, as well as Cooldown Start / End.\n\nIncludes 3 basic abilities: Teleport (or dash), Blink and Double Jump.",
		"LaunchPad.Card.PowerButton",
		{
			FGSCGridItemAction(
				EGSCActionType::OpenSample,
				"/GASCompanionExamples/Examples/CustomHUD/Maps/CustomHUD_Example_Map",
				"/GASCompanionExamples/Examples/CustomHUD",
				{},
				SampleCustomHUDManager
			),
			FGSCGridItemAction(EGSCActionType::Documentation, GetDocumentationURL("/working-with-ui"))
		}
	);

	GSCLaunchPadData::RegisterItem(
		"AGR Pro Integration Example",
		"",
		"Same map as GAS Companion Playground but using a Character setup with AGR Pro for locomotion, using the free Animation Starter Pack from Epic.\n\nThe Character has examples for Jump and Sprint abilities.",
		"LaunchPad.Card.SampleAGR",
		{
			FGSCGridItemAction(
				EGSCActionType::OpenSample,
				"/GASCompanionExamples/Examples/AGRPro/Maps/AGRPro_Sample_Map",
				"/GASCompanionExamples/Examples/AGRPro",
				{
					FGSCGridItemDependency(
						"AGR Pro Plugin",
						"AGRPRO",
						EGSCDependencyType::Module,
						"https://www.unrealengine.com/marketplace/en-US/product/agr-pro"
					),
					FGSCGridItemDependency(
						"Animation Starter Pack",
						"/Game/AnimStarterPack/UE4_Mannequin/Mesh/UE4_Mannequin_Skeleton",
						EGSCDependencyType::Content,
						"https://www.unrealengine.com/marketplace/en-US/product/animation-starter-pack"
					),
				},
				SampleAGRManager
			),
			FGSCGridItemAction(EGSCActionType::Documentation, GetDocumentationURL("/launch-pad"))
		}
	);

	GSCLaunchPadData::RegisterItem(
		"Paragon Countess: Melee Combo Ability",
		"",
		"This example map demonstrate the use of a melee ability with combo capabilities. It uses the base melee ability provided by Companion to implement a 3-hit combo using Paragon Countess character.",
		"LaunchPad.Card.Rogue",
		{
			FGSCGridItemAction(
				EGSCActionType::OpenSample,
				"/GASCompanionExamples/Examples/ParagonCountess/Maps/ParagonCountess_Example_Map",
				"/GASCompanionExamples/Examples/ParagonCountess",
				{
					FGSCGridItemDependency(
						"Paragon: Countess",
						"/Game/ParagonCountess/Characters/Heroes/Countess/Meshes/S_Countess_Skeleton",
						EGSCDependencyType::Content,
						"https://www.unrealengine.com/marketplace/en-US/product/paragon-countess"
					),
				},
				SampleParagonCountessManager
			),
			FGSCGridItemAction(EGSCActionType::Documentation, GetDocumentationURL("/melee-ability"))
		}
	);
}

void FGASCompanionExamplesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

FString FGASCompanionExamplesModule::GetDocumentationURL(FString InPath)
{
	static FString DocumentationURL = "https://gascompanion.github.io";
	// static FString DocumentationURL = "https://gascompanion-dev.netlify.app";
	if (InPath.IsEmpty())
	{
		return DocumentationURL;
	}

	if (!InPath.StartsWith("/"))
	{
		InPath = "/" + InPath;
	}

	return DocumentationURL + InPath;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGASCompanionExamplesModule, GASCompanionExamples)
