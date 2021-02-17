// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceXGameModeBase.h"



#include "PlayerControllerBase.h"
#include "ActorComponents/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PawnEnemy.h"
#include "Pawns/PawnPlayer.h"

int ASpaceXGameModeBase::GetNumberOfShips() const
{
	return Ships;
}

void ASpaceXGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Player)
	{
		Player->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnEnemy* DestroyedEnemy = Cast<APawnEnemy>(DeadActor))
	{
		DestroyedEnemy->HandleDestruction();
		Ships--;
		UpdateShips();
		if (Ships == 0)
		{
			HandleGameOver(true);
		}
	}
}


void ASpaceXGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ShipLogicRef = Cast<AShipLogic>(UGameplayStatics::GetActorOfClass(this, AShipLogic::StaticClass()));
	ShipLogicRef->SpawnShips();
	Ships = GetSpacecraftCount();
	Player = Cast<APawnPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();
}

int ASpaceXGameModeBase::GetPlayerHealth()
{
	if (!Player) return 0;
	return Player->FindComponentByClass<UHealthComponent>()->GetHealth();
}

int ASpaceXGameModeBase::GetPlayerDefaultHealth()
{
	if (!Player) return 0;
	return Player->FindComponentByClass<UHealthComponent>()->GetDefaultHealth();
}

void ASpaceXGameModeBase::RestartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Restarting..."));
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

int32 ASpaceXGameModeBase::GetSpacecraftCount()
{
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnEnemy::StaticClass(), EnemyActors);
	return EnemyActors.Num();
}

void ASpaceXGameModeBase::HandleGameOver(bool PlayerWon)
{
	UE_LOG(LogTemp, Warning, TEXT("Game over"));
	GameOver(PlayerWon);
	GetWorld()->GetTimerManager().SetTimer(RestartTimerHandle, this, &ASpaceXGameModeBase::RestartGame, 5.f, false);
}

void ASpaceXGameModeBase::SpawnShips()
{
	if (!EnemyShipType)
	{
		UE_LOG(LogTemp, Error, TEXT("No ship type selected in BP_SpaceXGameModeBase"));
		return;
	}
	
	FRotator SpawnRotation{0.f, 180.f, 0.f};
	int rows = 5;
	int cols = 8;
	float Spaceing = 400.f;
	float XPos = 1000.f;
	float YPos = -(((float)cols * Spaceing) / 2.f) - Spaceing / 2.f;
	for (int ix = 0; ix < rows; ++ix)
	{
		XPos += Spaceing;
		for (int iy = 0; iy < cols; ++iy)
		{
			YPos += Spaceing;
			FVector SpawnLocation{XPos, YPos, 0.f};
			APawnEnemy* TempShip = GetWorld()->SpawnActor<APawnEnemy>(EnemyShipType, SpawnLocation, SpawnRotation);
			if (TempShip)
			{
				TempShip->SetOwner(this);
			}
		}
		YPos = -(((float)cols * Spaceing) / 2.f) - Spaceing / 2.f;
	}
}
