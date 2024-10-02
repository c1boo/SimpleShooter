// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "Blueprint/UserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		UUserWidget* MainMenu = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
		if(MainMenu)
		{
			MainMenu->AddToViewport();
		}

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(MainMenu->TakeWidget());
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}
