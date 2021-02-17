// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipLogic.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceXInvaders/SpaceXGameModeBase.h"
// Sets default values
AShipLogic::AShipLogic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShipLogic::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ASpaceXGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (!EndTrigger) return;
	EndTrigger->OnActorBeginOverlap.AddDynamic(this, &AShipLogic::EndTriggerBeginOverlap);
	if (!RightTrigger) return;
	RightTrigger->OnActorBeginOverlap.AddDynamic(this, &AShipLogic::RightTriggerBeginOverlap);
	if (!LeftTrigger) return;
	LeftTrigger->OnActorBeginOverlap.AddDynamic(this, &AShipLogic::LeftTriggerBeginOverlap);
}

void AShipLogic::EndTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s, Hit: %s"), *OtherActor->GetHumanReadableName(), *OverlappedActor->GetHumanReadableName());
	if (!OtherActor->IsA(APawnEnemy::StaticClass()))
	{
		return;
	}
	GameModeRef->HandleGameOver(false);
}

void AShipLogic::RightTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	MovingRight = false;
	MovingForward = true;
	GetWorld()->GetTimerManager().SetTimer(SetMovingForwardFalseTimerHandle, this, &AShipLogic::SetMovingForwardFalse, 1.f, false);
}

void AShipLogic::LeftTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	MovingRight = true;
	MovingForward = true;
	GetWorld()->GetTimerManager().SetTimer(SetMovingForwardFalseTimerHandle, this, &AShipLogic::SetMovingForwardFalse, 1.f, false);
}

void AShipLogic::SetMovingForwardFalse()
{
	MovingForward = false;
}

void AShipLogic::SpawnShips()
{
	if (!EnemyShipType)
	{
		UE_LOG(LogTemp, Error, TEXT("No ship type selected in BP_ShipLogic"));
		return;
	}
	
	FRotator SpawnRotation{0.f, 180.f, 0.f};
	int rows = 5;
	int cols = 8;
	float Spaceing = 400.f;
	float XPos = 1500.f;
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



