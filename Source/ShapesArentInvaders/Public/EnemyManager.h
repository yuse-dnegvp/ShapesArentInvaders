// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHAPESARENTINVADERS_API UEnemyManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemiesRow();

	// Type of enemies to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> EnemyType = AEnemy::StaticClass();

	// Play Area top left coordinate
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector3f PlayAreaTopLeft = {0.0f, 0.0f, 1.0f};

	// Play Area bottom right coordinate
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector3f PlayAreaBottomRight = {0.0f, 1.0f, 0.0f};

	// Play Area bottom right coordinate
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberEnemiesPerRow = 5;

	// Spawned enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AEnemy*> Enemies;

		
};
