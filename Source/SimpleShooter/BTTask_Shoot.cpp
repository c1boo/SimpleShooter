// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	
	AShooterCharacter* OwnerPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!OwnerPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	OwnerPawn->Shoot();

	return EBTNodeResult::Succeeded;
}
