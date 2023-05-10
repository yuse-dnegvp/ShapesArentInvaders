// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeMain.generated.h"

class AEnemy;
class APlayerPawn;

/**
 *
 */
UCLASS()
class SHAPESARENTINVADERS_API AGameModeMain : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnEnemyHit(AEnemy* Target, APlayerPawn* Ofender);
	void OnEnemyHit_Implementation(AEnemy* Target, APlayerPawn* Ofender);

	UFUNCTION(BlueprintNativeEvent)
	void OnEnemyKilled(AEnemy* Target, APlayerPawn* Ofender);
	void OnEnemyKilled_Implementation(AEnemy* Target, APlayerPawn* Ofender);

	UFUNCTION(BlueprintNativeEvent)
	void OnAllEnemiesKilled();
	void OnAllEnemiesKilled_Implementation();
};
