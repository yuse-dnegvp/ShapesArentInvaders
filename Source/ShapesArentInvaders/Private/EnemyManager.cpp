// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

// Sets default values for this component's properties
UEnemyManager::UEnemyManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEnemyManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyManager::SpawnEnemiesRow()
{
	const float EnemiesIndentation =
		NumberEnemiesPerRow < 2 ? 0 : (PlayAreaBottomRight.Y - PlayAreaTopLeft.Y) / (NumberEnemiesPerRow - 1);
	for (int i = 0; i < NumberEnemiesPerRow; ++i)
	{
		AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyType, FVector(), FRotator());
		SpawnedEnemy->SetActorLocation({ 0.0f, PlayAreaTopLeft.Y + i * EnemiesIndentation, PlayAreaTopLeft.Z });
		Enemies.Add(SpawnedEnemy);

		UE_LOG(LogTemp, Display, TEXT("Enemy #%d has been spawned!"), Enemies.Num());
	}
}

