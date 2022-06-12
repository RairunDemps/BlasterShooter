// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/BSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

ABSBaseWeapon::ABSBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetRootComponent(CollisionComponent);

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(CollisionComponent);
    WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    if (HasAuthority())
    {
        CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
        CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
}

void ABSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ABSBaseWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
