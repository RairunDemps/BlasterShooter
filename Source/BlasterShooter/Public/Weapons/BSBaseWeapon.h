// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSBaseWeapon.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UWidgetComponent;

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

    void SetEquipped();

    virtual void Tick(float DeltaTime) override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor);
    virtual void NotifyActorEndOverlap(AActor* OtherActor);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* WidgetComponent;

    UPROPERTY(VisibleAnywhere, Category = "State", ReplicatedUsing = OnRep_WeaponState)
    EWeaponState WeaponState;

    virtual void BeginPlay() override;

private:
    void SetWeaponState(EWeaponState State);

    UFUNCTION()
    void OnRep_WeaponState();
};
