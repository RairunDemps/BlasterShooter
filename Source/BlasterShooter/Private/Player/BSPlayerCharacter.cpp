// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BSPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/BSBaseWeapon.h"
#include "Components/BSWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBSPlayerCharacter, All, All);

ABSPlayerCharacter::ABSPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
    SpringArmComponent->SetupAttachment(GetMesh());
    SpringArmComponent->TargetOffset = FVector(0.0f, 0.0f, 200.0f);
    SpringArmComponent->TargetArmLength = 600.0f;
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
    CameraComponent->bUsePawnControlRotation = false;

    WeaponComponent = CreateDefaultSubobject<UBSWeaponComponent>(TEXT("WeaponComponent"));
    WeaponComponent->SetIsReplicated(true);

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

bool ABSPlayerCharacter::IsWeaponEquipped() const
{
    return WeaponComponent && WeaponComponent->IsCurrentWeaponEquipped();
}

void ABSPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ABSPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABSPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ABSPlayerCharacter::PickupWeapon);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABSPlayerCharacter::CrouchButtonPressed);

    PlayerInputComponent->BindAxis("MoveForward", this, &ABSPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABSPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ABSPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ABSPlayerCharacter::AddControllerPitchInput);
}

void ABSPlayerCharacter::MoveForward(float Value)
{
    if (!Controller || Value == 0) return;

    const FRotator YawRotation{0.0f, Controller->GetControlRotation().Yaw, 0.0f};
    const FVector Direction{FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X)};
    AddMovementInput(Direction, Value);
}

void ABSPlayerCharacter::MoveRight(float Value)
{
    if (!Controller || Value == 0) return;

    const FRotator YawRotation{0.0f, Controller->GetControlRotation().Yaw, 0.0f};
    const FVector Direction{FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y)};
    AddMovementInput(Direction, Value);
}

void ABSPlayerCharacter::PickupWeapon()
{
    if (!WeaponComponent) return;

    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, ABSBaseWeapon::StaticClass());
    if (OverlappingActors.Num() <= 0) return;

    ABSBaseWeapon* WeaponToEquip = nullptr;
    for (const auto OverlappingActor : OverlappingActors)
    {
        WeaponToEquip = Cast<ABSBaseWeapon>(OverlappingActor);
        if (!WeaponToEquip) continue;

        WeaponComponent->TryEquipWeapon(WeaponToEquip);
        break;
    }
}

void ABSPlayerCharacter::CrouchButtonPressed()
{
    if (bIsCrouched)
    {
        UnCrouch();
    }
    else
    {
        Crouch();
    }
}
