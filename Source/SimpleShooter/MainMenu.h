// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable)
	void OnPlayButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitButtonClicked();
};
