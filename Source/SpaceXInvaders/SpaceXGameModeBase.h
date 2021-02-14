// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"


#include "SpaceXGameModeBase.generated.h"

/**
 * 
 */
class APawnEnemy;
class APawnPlayer;
class APlayerControllerBase;
UCLASS()
class SPACEXINVADERS_API ASpaceXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);
	int GetNumberOfShips() const;
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthUI(float Health, float DefaultHealth);
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameLoop")
	int32 StartDelay{3};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameLoop")
	int32 Score{0};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameLoop")
	int32 Ships{0};
	
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
    void UpdateShips();
	UFUNCTION(BlueprintImplementableEvent)
    void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
    void GameOver(bool PlayerWon);
	UFUNCTION(BlueprintCallable)
	int GetPlayerHealth();
	UFUNCTION(BlueprintCallable)
    int GetPlayerDefaultHealth();
private:
	APawnPlayer* Player;
	APlayerControllerBase* PlayerControllerRef;
	
	
	//APlayerControllerBase* PlayerControllerBaseRef;

	int32 GetSpacecraftCount();
	void HandleGameOver(bool PlayerWon);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipSpawner", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawnEnemy> EnemyShipType;
	void SpawnShips();
	
};
