// Copyright 2021 Mickael Daniel. All Rights Reserved.

#include "GASCompanionExamples.h"

#include "Core/Editor/GSCEditorInterface.h"
#include "Core/Editor/GSCExampleMapManager.h"
#include "Misc/CoreDelegates.h"

#define LOCTEXT_NAMESPACE "FGASCompanionExamplesModule"

void FGASCompanionExamplesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Display, TEXT("FGASCompanionExamplesModule StartupModule"))

	// FCoreDelegates::OnFEngineLoopInitComplete
	FCoreDelegates::OnFEngineLoopInitComplete.AddRaw(this, &FGASCompanionExamplesModule::SetupLaunchPadItems);
}

void FGASCompanionExamplesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FGASCompanionExamplesModule::SetupLaunchPadItems()
{
	UE_LOG(LogTemp, Display, TEXT("FGASCompanionExamplesModule SetupLaunchPadItems"))

	const TSharedPtr<IGSCEditorInterface> EditorInterface = IGSCEditorInterface::Get();
	if (!EditorInterface.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("FGASCompanionExamplesModule::SetupLaunchPadItems no interface"))
		return;
	}

	EditorInterface->ResetLaunchPadItems();

	const TSubclassOf<AGSCExampleMapManager> SamplePlaygroundManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_Playground_SampleManager.BP_Playground_SampleManager_C"));
	EditorInterface->RegisterLaunchPadItem(
		"GAS Companion Playground",
		"",
		"GAS Companion Example map with happy jumping AI and a basic shoot ability to test out the system.\n\nAlso include an example of a DefaultPawn and an Actor with an Ability System Component.",
		"LaunchPad.Card.SamplePlayground",
		{
			FGSCLaunchPadItemAction(
				EGSCLaunchPadActionType::OpenSample,
				"/GASCompanionExamples/Examples/Playground/Maps/GASCompanionExampleMap",
				"/GASCompanionExamples/Examples/Playground",
				{},
				SamplePlaygroundManager
			),
			FGSCLaunchPadItemAction(EGSCLaunchPadActionType::Documentation,GetDocumentationURL("/quick-start"))
		}
	);

	const TSubclassOf<AGSCExampleMapManager> SampleCustomHUDManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_CustomHUD_SampleManager.BP_CustomHUD_SampleManager_C"));
	EditorInterface->RegisterLaunchPadItem(
		"Custom HUD Example",
		"",
		"This example map demonstrate the use of a custom UI and specific HUD widget. It shows how GAS Companion HUD UserWidget can be used to listen for Gameplay Attributes, Gameplay Tags, and Gameplay Effects changes, as well as Cooldown Start / End.\n\nIncludes 3 basic abilities: Teleport (or dash), Blink and Double Jump.",
		"LaunchPad.Card.PowerButton",
		{
			FGSCLaunchPadItemAction(
				EGSCLaunchPadActionType::OpenSample,
				"/GASCompanionExamples/Examples/CustomHUD/Maps/CustomHUD_Example_Map",
				"/GASCompanionExamples/Examples/CustomHUD",
				{},
				SampleCustomHUDManager
			),
			FGSCLaunchPadItemAction(EGSCLaunchPadActionType::Documentation, GetDocumentationURL("/working-with-ui"))
		}

	);

	const TSubclassOf<AGSCExampleMapManager> SampleAGRManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_AGRPro_SampleManager.BP_AGRPro_SampleManager_C"));
	EditorInterface->RegisterLaunchPadItem(
		"AGR Pro Integration Example",
		"",
		"Same map as GAS Companion Playground but using a Character setup with AGR Pro for locomotion, using the free Animation Starter Pack from Epic.\n\nThe Character has examples for Jump and Sprint abilities.",
		"LaunchPad.Card.SampleAGR",
		{
			FGSCLaunchPadItemAction(
				EGSCLaunchPadActionType::OpenSample,
				"/GASCompanionExamples/Examples/AGRPro/Maps/AGRPro_Sample_Map",
				"/GASCompanionExamples/Examples/AGRPro",
				{
					FGSCLaunchPadItemDependency(
						"AGR Pro Plugin",
						"AGRPRO",
						"https://www.unrealengine.com/marketplace/en-US/product/agr-pro",
						EGSCLaunchPadDependencyType::Module
					),
					FGSCLaunchPadItemDependency(
						"Animation Starter Pack",
						"/Game/AnimStarterPack/UE4_Mannequin/Mesh/UE4_Mannequin_Skeleton",
						"https://www.unrealengine.com/marketplace/en-US/product/animation-starter-pack",
						EGSCLaunchPadDependencyType::Content
					)
				},
				SampleAGRManager
			),
			FGSCLaunchPadItemAction(EGSCLaunchPadActionType::Documentation, GetDocumentationURL("/launch-pad"))
		}
	);

	const TSubclassOf<AGSCExampleMapManager> SampleALSManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_ALS_SampleManager.BP_ALS_SampleManager_C"));
	EditorInterface->RegisterLaunchPadItem(
		"ALS Integration Example",
		"",
		"Based on ALS-Community plugin (ALSV4_CPP). Same map as ALS v4, but using GASCompanionExamples plugin acting as a bridge between GAS (using Companion) and ALS.\n\nThe map has examples for Jump and Combo abilities.",
		"LaunchPad.Card.SampleALS",
		{
			FGSCLaunchPadItemAction(
				EGSCLaunchPadActionType::OpenSample,
				"/GASCompanionExamples/Examples/ALS/Maps/GSC_ALS_Example_DemoLevel",
				"/GASCompanionALS",
				{
					FGSCLaunchPadItemDependency(
						"ALS-Community (ALSV4_CPP)",
						"ALSV4_CPP",
						"https://github.com/dyanikoglu/ALS-Community",
						EGSCLaunchPadDependencyType::Module
					),
					FGSCLaunchPadItemDependency(
						"GASCompanionALS",
						"GASCompanionALS",
						"https://github.com/GASCompanion/GASCompanionALS",
						EGSCLaunchPadDependencyType::Module
					),
				},
				SampleALSManager
			),
			FGSCLaunchPadItemAction(EGSCLaunchPadActionType::Documentation, "https://github.com/GASCompanion/GASCompanionALS")
		}
	);

	const TSubclassOf<AGSCExampleMapManager> SampleParagonCountessManager = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/GASCompanionExamples/Examples/Shared/SampleManagers/BP_ParagonCountess_SampleManager.BP_ParagonCountess_SampleManager_C"));
	EditorInterface->RegisterLaunchPadItem(
		"Paragon Countess: Melee Combo Ability",
		"",
		"This example map demonstrate the use of a melee ability with combo capabilities. It uses the base melee ability provided by Companion to implement a 3-hit combo using Paragon Countess character.",
		"LaunchPad.Card.Rogue",
		{
			FGSCLaunchPadItemAction(
				EGSCLaunchPadActionType::OpenSample,
				"/GASCompanionExamples/Examples/ParagonCountess/Maps/ParagonCountess_Example_Map",
				"/GASCompanionExamples/Examples/ParagonCountess",
				{
					FGSCLaunchPadItemDependency(
						"Paragon: Countess",
						"/Game/ParagonCountess/Characters/Heroes/Countess/Meshes/S_Countess_Skeleton",
						"https://www.unrealengine.com/marketplace/en-US/product/paragon-countess",
						EGSCLaunchPadDependencyType::Content
					),
				},
				SampleParagonCountessManager
			),
			FGSCLaunchPadItemAction(EGSCLaunchPadActionType::Documentation, GetDocumentationURL("/melee-ability"))
		}
	);
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
