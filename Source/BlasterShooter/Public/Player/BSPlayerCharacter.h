// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBSWeaponComponent;
class ABSBaseWeapon;

UCLASS()
class BLASTERSHOOTER_API ABSPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ABSPlayerCharacter();

    bool IsWeaponEquipped() const;
    bool IsAiming() const;

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBSWeaponComponent* WeaponComponent;

    virtual void BeginPlay() override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);

    void PickupWeapon();
    void CrouchButtonPressed();
};
