// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetLastKnownLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_SetLastKnownLocation::UBTService_SetLastKnownLocation()
{
	NodeName = TEXT("Update Last Known Location");
}

void UBTService_SetLastKnownLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Player)
	{
		return;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
}
