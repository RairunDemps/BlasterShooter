// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BSWeaponComponent.generated.h"

class ABSBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTERSHOOTER_API UBSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBSWeaponComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TryEquipWeapon(ABSBaseWeapon* Weapon);
    bool IsCurrentWeaponEquipped() const { return CurrentWeapon != nullptr; }

protected: 
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    int32 InventoryVolume = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
    TArray<ABSBaseWeapon*> Weapons;
	int32 CurrentWeaponIndex;

	UPROPERTY(Replicated)
    ABSBaseWeapon* CurrentWeapon;

	void AttachWeaponToSocket(ABSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void EquipWeapon(ABSBaseWeapon* Weapon, ACharacter* Owner);

	UFUNCTION(Server, Reliable)
    void Server_EquipWeapon(ABSBaseWeapon* Weapon, ACharacter* Owner);
};
