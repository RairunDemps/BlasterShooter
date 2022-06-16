// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BSPlayerAnimInstance.generated.h"

class ABSPlayerCharacter;

UCLASS()
class BLASTERSHOOTER_API UBSPlayerAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    void NativeInitializeAnimation() override;
    void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
    ABSPlayerCharacter* PlayerCharacter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float Speed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    bool bFalling;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    bool bMoving;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    bool bCrouch;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool bWeaponEquipped;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool bAiming;
};
