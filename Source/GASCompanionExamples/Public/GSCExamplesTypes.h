// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GSCExamplesTypes.generated.h"

class UTexture2D;

/** Structure that defines an ActionKeyMapping table entry, with their associated on screen display (text or icon) */
USTRUCT(BlueprintType)
struct FGSCExamplesActionKeyMappingsData : public FTableRowBase
{
	GENERATED_BODY()

public:

	/** The 'Name' column is the same as the ActionKeyName */

	/** Localized Text for the given ActionKeyName */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GSC|UI")
	FText ActionKeyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GSC|UI")
	UTexture2D* ActionIcon;
};
