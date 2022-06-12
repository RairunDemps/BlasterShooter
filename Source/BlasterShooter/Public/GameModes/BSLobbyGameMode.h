// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BSLobbyGameMode.generated.h"

UCLASS()
class BLASTERSHOOTER_API ABSLobbyGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    ABSLobbyGameMode(const FObjectInitializer& ObjectInitializer);
    void PostLogin(APlayerController* NewPlayer) override;
};
