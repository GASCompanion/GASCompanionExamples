// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerInput.h"
#include "GSCEXUserWidget.generated.h"

class AGSCExampleMapManager;

/**
 *
 */
UCLASS()
class GASCOMPANIONEXAMPLES_API UGSCEXUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GSCEX|UI")
	TMap<FName, TSubclassOf<AGSCExampleMapManager>> LevelNameToManagerMap;

	UFUNCTION(BlueprintPure, Category="GSCEX|UI")
	static FString GetInputKeyString(FKey Key);

	UFUNCTION(BlueprintPure, Category="GSCEX|UI")
	static AGSCExampleMapManager* GetManagerDefaultObject(TSubclassOf<AGSCExampleMapManager> ManagerClass);

	UFUNCTION(BlueprintPure, Category="GSCEX|UI")
	static TArray<FInputActionKeyMapping> GetManagerActionMappings(TSubclassOf<AGSCExampleMapManager> ManagerClass);

	UFUNCTION(BlueprintPure, Category="GSCEX|UI")
	static TArray<FInputAxisKeyMapping> GetManagerAxisMappings(TSubclassOf<AGSCExampleMapManager> ManagerClass);

	/** Populate a list of all defined action names */
	UFUNCTION(BlueprintCallable, Category = Settings)
	void GetInputActionNamesForMap(FName MapName, TArray<FName>& ActionNames) const;

	/** Populate a list of all defined axis names */
	UFUNCTION(BlueprintCallable, Category = Settings)
	void GetInputAxisNamesForMap(FName MapName, TArray<FName>& ActionNames) const;

	/** Populate a list of all defined action and axis names */
	UFUNCTION(BlueprintCallable, Category = Settings)
	void GetInputNamesForMap(FName MapName, TArray<FName>& InputNames) const;

};
