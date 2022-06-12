// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/BSPlayerAnimInstance.h"
#include "Player/BSPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBSPlayerAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    PlayerCharacter = Cast<ABSPlayerCharacter>(TryGetPawnOwner());
}

void UBSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!PlayerCharacter) return;

    FVector Velocity = PlayerCharacter->GetVelocity();
    Velocity.Z = 0.0f;
    Speed = Velocity.Size();
    bFalling = PlayerCharacter->GetCharacterMovement()->IsFalling();
    bMoving = PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0;
}
