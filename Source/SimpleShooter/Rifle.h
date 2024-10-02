// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

UCLASS()
class SIMPLESHOOTER_API ARifle : public AGun
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();
	
	virtual bool PullTrigger() override;
};
