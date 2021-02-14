// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnEnemy.h"

#include "SpaceXInvaders/SpaceXGameModeBase.h"

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
}

void APawnEnemy::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = GetActorLocation();
	GameModeRef = Cast<ASpaceXGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APawnEnemy::CheckFriendlyFire, FireRate, true);
}

void APawnEnemy::CheckFriendlyFire()
{
	FHitResult Hit{GetFirstHitInReach(ECollisionChannel::ECC_WorldDynamic, 500.f, false)};

	if (Hit.GetActor())
	{
		return;
	}
	
	Fire();
}

void APawnEnemy::AIMove(float MoveSpeed, float DeltaTime)
{
	if(!GameModeRef) return;
	MoveSpeed = MoveSpeed + 1000.f / (float)GameModeRef->GetNumberOfShips();
	if (MovingForward)
	{
		//move forward
		//UE_LOG(LogTemp, Warning, TEXT("MOVING FORWARD"));
		AddActorLocalOffset(FVector::ForwardVector * MoveSpeed * DeltaTime);
		//set spawnlocation if the ship far enough. MovingForward = false;
		if (SpawnLocation.X - GetActorLocation().X > 50.f)
		{
			MovingForward = false;
			SpawnLocation = GetActorLocation();
		}
	}
	else
	{
		//move sideways
		if (MovingRight)
		{
			//move right
			//UE_LOG(LogTemp, Warning, TEXT("MOVING RIGHT"));
			AddActorLocalOffset(FVector::RightVector * MoveSpeed * DeltaTime);
			if (SpawnLocation.Y - GetActorLocation().Y > 500.f)
			{
				MovingForward = true;
				MovingRight = false;
				SpawnLocation = GetActorLocation();
			}
		}
		else
		{
			//move left
			//UE_LOG(LogTemp, Warning, TEXT("MOVING LEFT"));
			AddActorLocalOffset(-FVector::RightVector * MoveSpeed * DeltaTime);
			if (SpawnLocation.Y - GetActorLocation().Y < -500.f)
			{
				MovingForward = true;
                MovingRight = true;
				SpawnLocation = GetActorLocation();
			}
		}
	}
}


