// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Pawns/PawnEnemy.h"

#include "ShipLogic.generated.h"

class ASpaceXGameModeBase;
UCLASS()
class SPACEXINVADERS_API AShipLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipLogic();
	void SpawnShips();
	bool MovingForward = false;
	bool MovingRight = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyShipType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawnEnemy> EnemyShipType;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	ATriggerVolume* RightTrigger;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	ATriggerVolume* LeftTrigger;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Triggers", meta = (AllowPrivateAccess = "true"))
	ATriggerVolume* EndTrigger;

	UFUNCTION()
	void EndTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void RightTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void LeftTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	ASpaceXGameModeBase* GameModeRef;

	void SetMovingForwardFalse();
	FTimerHandle SetMovingForwardFalseTimerHandle;
};
