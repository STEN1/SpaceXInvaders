// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlayer.h"

#include "SpaceXInvaders/ActorComponents/HealthComponent.h"

APawnPlayer::APawnPlayer()
{
}

void APawnPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APawnPlayer::Move(FVector MoveV, float Speed, float DeltaTime)
{
	AddActorLocalOffset(MoveV * DeltaTime * Speed);
	if (GetActorLocation().Y < -1800.f)
	{
		SetActorLocation({GetActorLocation().X, -1800.f, GetActorLocation().Z});
	}
	else if (GetActorLocation().Y > 1800)
	{
		SetActorLocation({GetActorLocation().X, 1800.f, GetActorLocation().Z});
	}
}

void APawnPlayer::HandleDestruction()
{
	Super::HandleDestruction();
	// Hide player

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
}

void APawnPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//float MouseX;
	//float MouseY;
	//UGameplayStatics::GetPlayerController(this, 0)->GetInputMouseDelta(MouseX, MouseY);
	float MouseXClamped{FMath::Clamp(MouseXInput, -8.f, 8.f)};
	//UE_LOG(LogTemp, Warning, TEXT("MouseXDelta: %f"), MouseX);
	//SetMoveVector(MoveForwardInput, MoveRightInput);
	//SetRotationRotator(MouseX);
	// Dont need to pass DeltaTime to this because we get the mouse delta for this tick.
	//Rotate(RotationRotator, RotationSpeed, 1.f);
	//Move(MoveVector, MoveSpeed, DeltaTime);
	Move({0.f, MouseXClamped, 0.f}, 5.f, 1.f);
	
}

void APawnPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnPlayer::SetMoveForwardInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnPlayer::SetMoveRightInput);
	PlayerInputComponent->BindAxis("MouseX", this, &APawnPlayer::SetMouseXInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnPlayer::Fire);
}


void APawnPlayer::SetMoveForwardInput(float Value)
{
	MoveForwardInput = Value;
}

void APawnPlayer::SetMoveRightInput(float Value)
{
	MoveRightInput = Value;
}

void APawnPlayer::SetMoveVector(float Forward, float Right, float Up)
{
	MoveVector = FVector(Forward,Right,Up).GetSafeNormal();
}

void APawnPlayer::SetMouseXInput(float Value)
{
	MouseXInput = Value;
}

void APawnPlayer::SetRotationRotator(float Yaw, float Pitch, float Roll)
{
	RotationRotator = FRotator(Pitch, Yaw, Roll);
}
