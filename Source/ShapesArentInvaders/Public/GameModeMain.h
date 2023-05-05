// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeMain.generated.h"

/**
 *
 */
UCLASS()
class SHAPESARENTINVADERS_API AGameModeMain : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnEnemyHit();
	void OnEnemyHit_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void OnEnemyKilled();
	void OnEnemyKilled_Implementation();

	UFUNCTION(BlueprintCallable)
	void QuitGame();
};
