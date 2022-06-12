// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSBaseWeapon.generated.h"

class USkeletalMeshComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    Initial UMETA(DisplayName = "Initial state"),
    Equipped UMETA(DisplayName = "Equipped"),
    Dropped UMETA(DisplayName = "Dropped")
};

UCLASS()
class BLASTERSHOOTER_API ABSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ABSBaseWeapon();
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere)
    EWeaponState WeaponState;

    virtual void BeginPlay() override;
};
