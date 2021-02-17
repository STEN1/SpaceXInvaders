// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnEnemy.h"

#include "SpaceXInvaders/SpaceXGameModeBase.h"
#include "SpaceXInvaders/ShipLogic.h"
#include "SpaceXInvaders/Pawns/PawnPlayer.h"

APawnEnemy::APawnEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APawnEnemy::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void APawnEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AIMove(200.f, DeltaTime);
	if (bInFront) FireWhenPlayerSpoted();
}

void APawnEnemy::FireWhenPlayerSpoted()
{
	FHitResult Hit{GetFirstHitInReach(ECollisionChannel::ECC_WorldDynamic, 20000.f, false)};

	if (!Hit.GetActor()) return;
	
	if (Hit.GetActor()->IsA(APawnPlayer::StaticClass()) && bCanFireAtPlayer)
	{
		Fire();
		bCanFireAtPlayer = false;
		GetWorld()->GetTimerManager().SetTimer(FireAtPlayerTimerHandle,this , &APawnEnemy::SetFireAtPlayerTrue, FireRate, false);
	}
	
}

void APawnEnemy::SetFireAtPlayerTrue()
{
	bCanFireAtPlayer = true;
}

void APawnEnemy::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = GetActorLocation();
	GameModeRef = Cast<ASpaceXGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ShipLogicRef = Cast<AShipLogic>(UGameplayStatics::GetActorOfClass(this, AShipLogic::StaticClass()));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APawnEnemy::CheckFriendlyFire, FireRate * 2.f, true);
}

void APawnEnemy::CheckFriendlyFire()
{
	FHitResult Hit{GetFirstHitInReach(ECollisionChannel::ECC_WorldDynamic, 500.f, false)};

	if (Hit.GetActor())
	{
		return;
	}
	bInFront = true;
	Fire();
}

void APawnEnemy::AIMove(float MoveSpeed, float DeltaTime)
{
	MoveSpeed = MoveSpeed + 1000.f / (float)GameModeRef->GetNumberOfShips();
	if (ShipLogicRef->MovingForward)
	{
		AddActorLocalOffset(FVector::ForwardVector * MoveSpeed * DeltaTime);
	}
	else
	{
		if (ShipLogicRef->MovingRight)
		{
			AddActorLocalOffset(FVector::RightVector * MoveSpeed * DeltaTime);
		}
		else
		{
			AddActorLocalOffset(-FVector::RightVector * MoveSpeed * DeltaTime);
		}
	}


	
	// Old ship moving logic. Not what i wanted.
	//
	// 
	// if(!GameModeRef) return;
	// MoveSpeed = MoveSpeed + 1000.f / (float)GameModeRef->GetNumberOfShips();
	// if (MovingForward)
	// {
	// 	//move forward
	// 	//UE_LOG(LogTemp, Warning, TEXT("MOVING FORWARD"));
	// 	AddActorLocalOffset(FVector::ForwardVector * MoveSpeed * DeltaTime);
	// 	//set spawnlocation if the ship far enough. MovingForward = false;
	// 	if (SpawnLocation.X - GetActorLocation().X > 50.f)
	// 	{
	// 		MovingForward = false;
	// 		SpawnLocation = GetActorLocation();
	// 	}
	// }
	// else
	// {
	// 	//move sideways
	// 	if (MovingRight)
	// 	{
	// 		//move right
	// 		//UE_LOG(LogTemp, Warning, TEXT("MOVING RIGHT"));
	// 		AddActorLocalOffset(FVector::RightVector * MoveSpeed * DeltaTime);
	// 		if (SpawnLocation.Y - GetActorLocation().Y > 500.f)
	// 		{
	// 			MovingForward = true;
	// 			MovingRight = false;
	// 			SpawnLocation = GetActorLocation();
	// 		}
	// 	}
	// 	else
	// 	{
	// 		//move left
	// 		//UE_LOG(LogTemp, Warning, TEXT("MOVING LEFT"));
	// 		AddActorLocalOffset(-FVector::RightVector * MoveSpeed * DeltaTime);
	// 		if (SpawnLocation.Y - GetActorLocation().Y < -500.f)
	// 		{
	// 			MovingForward = true;
 //                MovingRight = true;
	// 			SpawnLocation = GetActorLocation();
	// 		}
	// 	}
	// }
}


