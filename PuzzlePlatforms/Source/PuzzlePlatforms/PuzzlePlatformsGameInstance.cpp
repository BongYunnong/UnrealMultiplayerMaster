// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Menu/WBP_MainMenu"));
	if (MenuBPClass.Class != nullptr) {
		MenuClass = MenuBPClass.Class;
	}
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/Menu/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class != nullptr) {
		InGameMenuClass = InGameMenuBPClass.Class;
	}
	UE_LOG(LogTemp, Warning, TEXT("GameInsatnce Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInsatnce Init"));
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass == nullptr) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (Menu == nullptr) return;
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (InGameMenuClass == nullptr) return;
	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (InGameMenu == nullptr) return;
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (Menu != nullptr) {
		Menu->Teardown();
	}
	
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Exec Host"));

	UWorld* World = GetWorld();
	if (World == nullptr) return;
	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");  
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr) {
		Menu->Teardown();
	}
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Exec Join : %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController != nullptr) {
		PlayerController->ClientTravel(Address, TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController != nullptr) {
		PlayerController->ClientTravel("/Game/ThirdPerson/Maps/MainMenu", TRAVEL_Absolute);
	}
}
