// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BSPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
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
