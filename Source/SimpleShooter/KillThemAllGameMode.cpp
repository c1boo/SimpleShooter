// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillThemAllGameMode::PawnKilled(APawn* KilledPawn)
{
	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
	if (PlayerController)
	{
		EndGame(false);
		return;
	}

	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			Controller->DisableInput(PlayerController);
		}
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
