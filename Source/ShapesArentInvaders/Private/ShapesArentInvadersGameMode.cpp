// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapesArentInvadersGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

void AShapesArentInvadersGameMode::OnEnemyHit_Implementation()
{

}

void AShapesArentInvadersGameMode::OnEnemyKilled_Implementation()
{

}

void AShapesArentInvadersGameMode::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
