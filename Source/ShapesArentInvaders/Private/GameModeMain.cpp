// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeMain.h"
#include "Kismet/KismetSystemLibrary.h"

void AGameModeMain::OnEnemyHit_Implementation()
{

}

void AGameModeMain::OnEnemyKilled_Implementation()
{

}

void AGameModeMain::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
