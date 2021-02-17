// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "Engine/TriggerVolume.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	InitialLifeSpan = 10.f;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::BeginOverlap);
	
}

void AProjectileBase::Move(FVector MoveV, float MoveSpeed)
{
	AddActorLocalOffset(MoveV * GetWorld()->DeltaTimeSeconds * MoveSpeed);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(MoveDir, MovementSpeed);
}

void AProjectileBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}
	if (OtherActor->IsA(ATriggerVolume::StaticClass()))
	{
		return;
	}
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(),this , DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		//GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
		Destroy();
	}
}

