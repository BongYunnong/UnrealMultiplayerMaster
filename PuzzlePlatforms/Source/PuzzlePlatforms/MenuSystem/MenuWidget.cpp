// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"


void UMenuWidget::Setup()
{
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (World == nullptr)return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController != nullptr) {
		FInputModeUIOnly InputModeData;
		//InputModeData.SetWidgetToFocus(this->TakeWidget());
		this->bIsFocusable = true;
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputModeData);

		PlayerController->bShowMouseCursor = true;
	}
}

void UMenuWidget::Teardown()
{
	this->RemoveFromParent();
	UWorld* World = GetWorld();
	if (World == nullptr)return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController != nullptr) {
		FInputModeGameOnly InputModeData;
		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = false;
	}
}


void UMenuWidget::SetMenuInterface(IMenuInterface* menuInterface)
{
	this->MenuInterface = menuInterface;
}