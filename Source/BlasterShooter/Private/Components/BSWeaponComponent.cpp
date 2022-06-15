// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BSWeaponComponent.h"
#include "Weapons/BSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

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
}

void UBSWeaponComponent::TryEquipWeapon(ABSBaseWeapon* Weapon)
{
    if (!Weapon) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    EquipWeapon(Weapon, Character);
    Server_EquipWeapon(Weapon, Character);
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
