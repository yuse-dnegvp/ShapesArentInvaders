// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyManager.generated.h"

class APlayerPawn;
class AProjectile;
class AGameModeMain;

USTRUCT(BlueprintType)
struct FEnemiesRow
{
	GENERATED_BODY()

	// Array of the enemies in the row.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AEnemy*> Enemies;
};


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

	// Play Area is the area where enemies are moving in
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBox2D PlayArea2D = {{-500.0f, 0.0f}, {500.0f, 1000.0f}};

	// Spawn Area is the area where enemies are spawning in
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBox2D SpawnArea2D = {{-400.0f, 0.0f}, {400.0f, 800.0f}};

	// Play Area bottom right coordinate
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberEnemiesPerRow = 5;

	// Initial speed of horizontal movement of the enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalMovementInitialSpeed = 25.0f;

	// Max speed of horizontal movement of the enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalMovementMaxSpeed = 75.0f;

	// Spawned enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEnemiesRow> EnemyRows;

private:
	float GetEnemiesIndentation(int EnemiesPerRow) const;
	float GetEnemyInitialHorizontalPosition(int Index, float EnemiesIndentation) const;
	void AnimateHorizontalMovement(float DeltaTime);

	UFUNCTION()
	void OnEnemyHit(AEnemy* Target, AProjectile* Projectile, APlayerPawn* Ofender);

	enum class EnemiesHorizontalMovementDirection : uint8 { Left, Right };
	EnemiesHorizontalMovementDirection HorizontalMovementDirection = EnemiesHorizontalMovementDirection::Right;
	float HorizontalMovementShift = 0.0f;

	AGameModeMain* GameMode;
};
