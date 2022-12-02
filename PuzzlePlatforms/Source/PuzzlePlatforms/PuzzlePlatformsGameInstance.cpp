// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInsatnce Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInsatnce Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Exec Host"));

	UWorld* World = GetWorld();
	if (World == nullptr) return;
	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");  
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Exec Join : %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController != nullptr) {
		PlayerController->ClientTravel(Address, TRAVEL_Absolute);
	}
}
