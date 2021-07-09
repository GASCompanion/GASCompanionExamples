// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GSCEXUserWidget.h"
#include "Core/Editor/GSCExampleMapManager.h"

FString UGSCEXUserWidget::GetInputKeyString(const FKey Key)
{
	return Key.GetFName().ToString();
}

AGSCExampleMapManager* UGSCEXUserWidget::GetManagerDefaultObject(const TSubclassOf<AGSCExampleMapManager> ManagerClass)
{
	return Cast<AGSCExampleMapManager>(ManagerClass->GetDefaultObject());
}

TArray<FInputActionKeyMapping> UGSCEXUserWidget::GetManagerActionMappings(const TSubclassOf<AGSCExampleMapManager> ManagerClass)
{
	if (!IsValid(ManagerClass))
	{
		return {};
	}

	AGSCExampleMapManager* SampleManager = Cast<AGSCExampleMapManager>(ManagerClass->GetDefaultObject());
	if (!SampleManager)
	{
		return {};
	}

	return SampleManager->ActionMappings;
}

TArray<FInputAxisKeyMapping> UGSCEXUserWidget::GetManagerAxisMappings(const TSubclassOf<AGSCExampleMapManager> ManagerClass)
{
	if (!IsValid(ManagerClass))
	{
		return {};
	}

	AGSCExampleMapManager* SampleManager = Cast<AGSCExampleMapManager>(ManagerClass->GetDefaultObject());
	if (!SampleManager)
	{
		return {};
	}

	return SampleManager->AxisMappings;
}

void UGSCEXUserWidget::GetInputActionNamesForMap(const FName MapName, TArray<FName>& ActionNames) const
{
	ActionNames.Reset();

	const TSubclassOf<AGSCExampleMapManager>* ManagerClassPtr = LevelNameToManagerMap.Find(MapName);
	if (!ManagerClassPtr)
	{
		return;
	}

	const TSubclassOf<AGSCExampleMapManager> ManagerClass = *ManagerClassPtr;
	if (!ManagerClass)
	{
		return;
	}

	TArray<FInputActionKeyMapping> ActionMappings = GetManagerActionMappings(ManagerClass);
	for (FInputActionKeyMapping ActionMapping : ActionMappings)
	{
		ActionNames.AddUnique(ActionMapping.ActionName);
	}
}

void UGSCEXUserWidget::GetInputAxisNamesForMap(const FName MapName, TArray<FName>& ActionNames) const
{
	ActionNames.Reset();

	const TSubclassOf<AGSCExampleMapManager>* ManagerClassPtr = LevelNameToManagerMap.Find(MapName);
	if (!ManagerClassPtr)
	{
		return;
	}

	const TSubclassOf<AGSCExampleMapManager> ManagerClass = *ManagerClassPtr;
	if (!ManagerClass)
	{
		return;
	}


	TArray<FInputAxisKeyMapping> AxisMappings = GetManagerAxisMappings(ManagerClass);
	for (FInputAxisKeyMapping AxisMapping : AxisMappings)
	{
		ActionNames.AddUnique(AxisMapping.AxisName);
	}
}

void UGSCEXUserWidget::GetInputNamesForMap(const FName MapName, TArray<FName>& InputNames) const
{
	GetInputActionNamesForMap(MapName, InputNames);
	GetInputAxisNamesForMap(MapName, InputNames);
}
