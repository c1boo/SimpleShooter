// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Kismet/GameplayStatics.h"

void UMainMenu::OnPlayButtonClicked()
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(this, FName("DefaultLevel"), true);
}

void UMainMenu::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
