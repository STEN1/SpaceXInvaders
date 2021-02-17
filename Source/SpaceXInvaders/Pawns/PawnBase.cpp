// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"


#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(StaticMeshComponent);

}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APawnBase::Move(FVector MoveV, float MoveSpeed, float DeltaTime)
{
	AddActorLocalOffset(MoveV * DeltaTime * MoveSpeed);
}

void APawnBase::Rotate(FRotator RotationR, float RotationSpeed, float DeltaTime)
{
	AddActorLocalRotation(RotationR * DeltaTime * RotationSpeed);
}

void APawnBase::Fire()
{
	if (Projectile)
	{
		FVector ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator ProjectileSpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(Projectile, ProjectileSpawnLocation, ProjectileSpawnRotation);
		if (TempProjectile)
		{
			TempProjectile->SetOwner(this);
		}
	}
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnBase::HandleDestruction()
{
	
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	//GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}

FHitResult APawnBase::GetFirstHitInReach(ECollisionChannel CollisionChannel, float Reach, bool DrawTraceLine) const
{
	FVector PawnLocation{GetActorLocation()};
	FRotator PawnRotation{GetActorRotation()};
	FVector LineTraceEnd{PawnLocation + (PawnRotation.Vector() * Reach)};
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, this);
	GetWorld()->LineTraceSingleByObjectType(
        Hit,
        PawnLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(CollisionChannel),
        TraceParams
    );

	if (DrawTraceLine)
	{
		DrawDebugLine(
        GetWorld(),
        PawnLocation,
        LineTraceEnd,
        FColor(0, 255, 0),
        false,
        0.f,
        0,
        5.f
    );
	}
	// See what it hits
	// if (Hit.GetActor())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
	// }
	return Hit;
}

