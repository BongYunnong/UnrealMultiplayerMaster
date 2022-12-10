// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MenuInterface.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (Host == nullptr) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (Join == nullptr) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (CancelButton == nullptr) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	if (EnterButton == nullptr) return false;
	EnterButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	if (QuitButton == nullptr) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr) {
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher == nullptr) return;
	if (JoinMenu == nullptr) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (MenuSwitcher == nullptr) return;
	if (MainMenu == nullptr) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr) {
		const FString& Address = IPAddressField->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::QuitPressed()
{
	UWorld* World = GetWorld();
	if (World == nullptr)return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController != nullptr) {
		PlayerController->ConsoleCommand("quit");
	}
}
