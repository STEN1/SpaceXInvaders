// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SPACEXINVADERS_API APawnPlayer : public APawnBase
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	APawnPlayer();

	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Move(FVector MoveV, float MoveSpeed, float DeltaTime) override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void SetMoveForwardInput(float Value);
	void SetMoveRightInput(float Value);
	void SetMoveVector(float Forward, float Right, float Up = 0.f);
	float MoveForwardInput{0.f};
	float MoveRightInput{0.f};
	float MoveSpeed{1200.f};
	FVector MoveVector{FVector::ZeroVector};

	void SetMouseXInput(float Value);
	void SetRotationRotator(float Yaw, float Pitch = 0.f, float Roll = 0.f);
	float MouseXInput{0.f};
	float RotationSpeed{2.f};
	FRotator RotationRotator{FRotator::ZeroRotator};
	
};
