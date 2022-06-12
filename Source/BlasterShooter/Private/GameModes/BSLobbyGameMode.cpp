// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BSLobbyGameMode.h"
#include "Player/BSPlayerCharacter.h"
#include "GameFramework/GameState.h"

ABSLobbyGameMode::ABSLobbyGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    DefaultPawnClass = ABSPlayerCharacter::StaticClass();
    bUseSeamlessTravel = true;
}

void ABSLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (!GetWorld() || !GameState.Get()) return;

    int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
    if (NumberOfPlayers >= 2)
    {
        GetWorld()->ServerTravel("/Game/BlasterShooter/Maps/Arena/Arena?listen");
    }
}
