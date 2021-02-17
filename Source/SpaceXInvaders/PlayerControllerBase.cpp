// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "SpaceXInvaders/Pawns/PawnPlayer.h"

void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	APawnPlayer* PlayerPawn = Cast<APawnPlayer>(GetPawn());
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("MISSING PLAYER PAWN PlayerControllerBase.cpp"));
		return;
	}
	if (SetPlayerEnabled)
	{
		PlayerPawn->EnableInput(this);
	}
	else
	{
		PlayerPawn->DisableInput(this);
		//PlayerPawn->SetMouseXInput(0.f);
	}

	// bShowMouseCursor = SetPlayerEnabled;
}
