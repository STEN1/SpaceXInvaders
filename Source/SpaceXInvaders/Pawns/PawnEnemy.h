// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"


#include "PawnEnemy.generated.h"

class AShipLogic;
/**
 * 
 */
class ASpaceXGameModeBase;
UCLASS()
class SPACEXINVADERS_API APawnEnemy : public APawnBase
{
	GENERATED_BODY()
public:
	APawnEnemy();
	virtual void HandleDestruction() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	void CheckFriendlyFire();
	void AIMove(float MoveSpeed, float DeltaTime);

private:
	void FireWhenPlayerSpoted();
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float FireRate{2};
	FVector SpawnLocation;
	bool bInFront{false};
	void SetFireAtPlayerTrue();
	bool bCanFireAtPlayer{true};
	FTimerHandle FireAtPlayerTimerHandle;
	ASpaceXGameModeBase* GameModeRef;
	AShipLogic* ShipLogicRef;
	
};
