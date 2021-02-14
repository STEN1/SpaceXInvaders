// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceXInvaders/SpaceXGameModeBase.h"
#include "SpaceXInvaders/Pawns/PawnEnemy.h"
#include "SpaceXInvaders/Pawns/PawnPlayer.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

int UHealthComponent::GetHealth() const
{
	return Health;
}

int UHealthComponent::GetDefaultHealth() const
{
	return DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDmg);
	GameModeRef = Cast<ASpaceXGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	// ...
	
}

void UHealthComponent::TakeDmg(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || Health <= 0)
	{
		return;
	}
	if (DamageCauser->GetOwner()->IsA(APawnEnemy::StaticClass()) && GetOwner()->IsA(APawnEnemy::StaticClass()))
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);
	UE_LOG(LogTemp, Warning, TEXT("DamageCauserOwner: %s"), *DamageCauser->GetOwner()->GetHumanReadableName());
	if (GetOwner()->IsA(APawnPlayer::StaticClass()))
	{
		GameModeRef->UpdateHealthUI(Health, DefaultHealth);
	}
	if (Health <= 0)
	{
		if (GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to GameMode"));
		}
	}
}




