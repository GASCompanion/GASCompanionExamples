// Copyright 2021 Mickael Daniel. All Rights Reserved.


#include "Attributes/XPAttributeSet.h"
#include "Actors/Characters/GSCCharacterBase.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

// Sets default values
UXPAttributeSet::UXPAttributeSet()
{
	// Set default values for this Set Attributes here
}

void UXPAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    // This is called whenever attributes change, so for max attributes we want to scale the current totals to match
    Super::PreAttributeChange(Attribute, NewValue);

    // Set adjust code here
    //
    // Example:
    //
    // If a Max value changes, adjust current to keep Current % of Current to Max
    //
    // if (Attribute == GetMaxHealthAttribute())
    // {
    //     AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
    // }
}

void UXPAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    AGSCCharacterBase* SourceCharacter = nullptr;
    AGSCCharacterBase* TargetCharacter = nullptr;
    GetCharactersFromContext(Data, SourceCharacter, TargetCharacter);

    const FGameplayTagContainer SourceTags = GetSourceTagsFromContext(Data);
    const FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();

    // Get Minimum Clamp value for this attribute, if it is available
    const float ClampMinimumValue = GetClampMinimumValueFor(Data.EvaluatedData.Attribute);

    // Compute the delta between old and new, if it is available
    float DeltaValue = 0;
    if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
    {
        // If this was additive, store the raw delta value to be passed along later
        DeltaValue = Data.EvaluatedData.Magnitude;
    }

    // Set clamping or handling or "meta" attributes here (like damages)

    // TODO: Generate PostGameplayEffectExecute content from attributes list as input
    // if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    // {
    //     // Handle other health changes. Health loss should go through Damage meta attribute
    //     SetHealth(FMath::Clamp(GetHealth(), ClampMinimumValue, GetMaxHealth()));
    //
    //     if (TargetCharacter)
    //     {
    //         TargetCharacter->HandleAttributeChange(GetHealthAttribute(), DeltaValue, SourceTags);
    //         TargetCharacter->HandleHealthChange(DeltaValue, SourceTags);
    //     }
    // }
}

void UXPAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
        
    DOREPLIFETIME_CONDITION_NOTIFY(UXPAttributeSet, CurrentXP, COND_None, REPNOTIFY_Always);
    
    DOREPLIFETIME_CONDITION_NOTIFY(UXPAttributeSet, NextLevelXPThreshold, COND_None, REPNOTIFY_Always);
    
    DOREPLIFETIME_CONDITION_NOTIFY(UXPAttributeSet, Level, COND_None, REPNOTIFY_Always);
}

void UXPAttributeSet::OnRep_CurrentXP(const FGameplayAttributeData& OldCurrentXP)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UXPAttributeSet, CurrentXP, OldCurrentXP);
}

void UXPAttributeSet::OnRep_NextLevelXPThreshold(const FGameplayAttributeData& OldNextLevelXPThreshold)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UXPAttributeSet, NextLevelXPThreshold, OldNextLevelXPThreshold);
}

void UXPAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UXPAttributeSet, Level, OldLevel);
}
