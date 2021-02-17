// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "ShipLogic.h"
#include "Engine/TriggerVolume.h"
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
	UFUNCTION(BlueprintCallable)
    int GetNumberOfShips() const;
	void ActorDied(AActor* DeadActor);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthUI(float Health, float DefaultHealth);
	void HandleGameOver(bool PlayerWon);
protected:

	
	
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

	int32 Ships{0};
	
	//APlayerControllerBase* PlayerControllerBaseRef;
	void RestartGame();
	int32 GetSpacecraftCount();
	
	FTimerHandle RestartTimerHandle;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ShipSpawner", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawnEnemy> EnemyShipType;
	void SpawnShips();
	AShipLogic* ShipLogicRef;
	
};
