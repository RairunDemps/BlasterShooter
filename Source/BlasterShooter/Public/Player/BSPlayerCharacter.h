// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BLASTERSHOOTER_API ABSPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ABSPlayerCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    virtual void BeginPlay() override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
};
