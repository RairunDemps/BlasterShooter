// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/BSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Player/BSPlayerCharacter.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogBSBaseWeapon, All, All)

ABSBaseWeapon::ABSBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    WeaponState = EWeaponState::Initial;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SetRootComponent(CollisionComponent);

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(CollisionComponent);
    WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
    WidgetComponent->SetupAttachment(CollisionComponent);
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    WidgetComponent->SetDrawAtDesiredSize(true);
    WidgetComponent->SetVisibility(false);
}

void ABSBaseWeapon::SetEquipped()
{
    SetWeaponState(EWeaponState::Equipped);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ABSBaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABSBaseWeapon, WeaponState);
}

void ABSBaseWeapon::SetWeaponState(EWeaponState State)
{
    if (WeaponState == State) return;

    WeaponState = State;
}

void ABSBaseWeapon::OnRep_WeaponState()
{
    switch (WeaponState)
    {
        case EWeaponState::Equipped:
            CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            break;
        default: break;
    }
}

void ABSBaseWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABSBaseWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (!OtherActor || !WidgetComponent || WidgetComponent->IsVisible()) return;

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (!Pawn || !Pawn->IsLocallyControlled()) return;

    WidgetComponent->SetVisibility(true);
}

void ABSBaseWeapon::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    if (!OtherActor || !WidgetComponent) return;

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (!Pawn || !Pawn->IsLocallyControlled()) return;

    WidgetComponent->SetVisibility(false);
}
