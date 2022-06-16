// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BSWeaponComponent.h"
#include "Weapons/BSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogBSWeaponComponent, All, All)

UBSWeaponComponent::UBSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UBSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBSWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBSWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UBSWeaponComponent, CurrentWeapon);
    DOREPLIFETIME(UBSWeaponComponent, bAiming);
}

void UBSWeaponComponent::TryEquipWeapon(ABSBaseWeapon* Weapon)
{
    if (!Weapon) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    EquipWeapon(Weapon, Character);
    Server_EquipWeapon(Weapon, Character);
}

void UBSWeaponComponent::EnableAiming()
{
    bAiming = true;
    Server_SetAiming(bAiming);
}

void UBSWeaponComponent::DisableAiming()
{
    bAiming = false;
    Server_SetAiming(bAiming);
}

void UBSWeaponComponent::AttachWeaponToSocket(ABSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UBSWeaponComponent::EquipWeapon(ABSBaseWeapon* Weapon, ACharacter* Owner)
{
    Weapon->SetOwner(Owner);
    Weapon->SetEquipped();
    Weapons.Add(Weapon);
    CurrentWeapon = Weapon;
    AttachWeaponToSocket(Weapon, Owner->GetMesh(), WeaponEquipSocketName);
}

void UBSWeaponComponent::Server_EquipWeapon_Implementation(ABSBaseWeapon* Weapon, ACharacter* Owner)
{
    EquipWeapon(Weapon, Owner);
}

void UBSWeaponComponent::Server_SetAiming_Implementation(bool bAimingValue)
{
    bAiming = bAimingValue;
}
