// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "PlayerPawn.h"
#include "Projectile.h"
#include "GameModeMain.h"

// Sets default values for this component's properties
UEnemyManager::UEnemyManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AGameModeMain>(GetWorld()->GetAuthGameMode());
}


// Called every frame
void UEnemyManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AnimateHorizontalMovement(DeltaTime);
}

void UEnemyManager::SpawnEnemiesRow()
{
	const float EnemiesIndentation = GetEnemiesIndentation(NumberEnemiesPerRow);
	FEnemiesRow newRow;
	for (int i = 0; i < NumberEnemiesPerRow; ++i)
	{
		const FVector Location{0.0f, GetEnemyInitialHorizontalPosition(i, EnemiesIndentation), SpawnArea2D.Max.Y};
		AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyType, Location, FRotator());

		SpawnedEnemy->Strength = static_cast<EEnemyStrength>(FMath::RandRange(0, static_cast<int>(EEnemyStrength::LAST_ELEMENT)));
		SpawnedEnemy->UpdateMaterial();
		SpawnedEnemy->OnHit.AddDynamic(this, &UEnemyManager::OnEnemyHit);
		newRow.Enemies.Add(SpawnedEnemy);
	}

	EnemyRows.Add(newRow);

	UE_LOG(LogTemp, Display, TEXT("Enemies row #%d has been spawned!"), EnemyRows.Num());
}

float UEnemyManager::GetEnemiesIndentation(int EnemiesPerRow) const
{
	return EnemiesPerRow < 2 ? 0 : SpawnArea2D.GetSize().X / (EnemiesPerRow - 1);
}

float UEnemyManager::GetEnemyInitialHorizontalPosition(int Index, float EnemiesIndentation) const
{
	return SpawnArea2D.Min.X + Index * EnemiesIndentation;
}

void UEnemyManager::AnimateHorizontalMovement(float DeltaTime)
{
	for (const auto& row : EnemyRows)
	{
		const int NumberEnemies = row.Enemies.Num();
		if (NumberEnemies < 1)
		{
			continue;
		}

		// Determine a horizontal space that enemies move in.
		const float MovementSpace =
			FMath::Min(SpawnArea2D.Min.X - PlayArea2D.Min.X, PlayArea2D.Max.X - SpawnArea2D.Max.X);

		// Calculate the movement speed of enemies.
		const float LastMovementProgress = (HorizontalMovementShift / MovementSpace + 1.0f) / 2.0f;
		const float AnimationSpeed = HorizontalMovementInitialSpeed + HorizontalMovementMaxSpeed * FMath::Sin(LastMovementProgress * PI);

		// Calculate the next step in the horizontal move (either left or right).
		// Change the movement direction, if we reached the edge of the play area.
		float AnimationDelta = DeltaTime * AnimationSpeed;
		if (HorizontalMovementDirection == EnemiesHorizontalMovementDirection::Left)
		{
			if (HorizontalMovementShift - AnimationDelta < -MovementSpace)
			{
				HorizontalMovementDirection = EnemiesHorizontalMovementDirection::Right;
			}
		}
		else
		{
			if (HorizontalMovementShift + AnimationDelta > MovementSpace)
			{
				HorizontalMovementDirection = EnemiesHorizontalMovementDirection::Left;
			}
		}
		if (HorizontalMovementDirection == EnemiesHorizontalMovementDirection::Left)
		{
			AnimationDelta *= -1;
		}

		// Apply the calculated step.
		HorizontalMovementShift += AnimationDelta;

#if 0
		UE_LOG(LogTemp, Display, TEXT(">>> Progress: %f; Speed: %f; Horizontal Shift: %f"),
			HorizontalMovementShift / MovementSpace, AnimationSpeed, HorizontalMovementShift);
#endif

		// Shift enemies horizontally in accordance with the calculated value
		const float EnemiesIndentation = GetEnemiesIndentation(row.Enemies.Num());
		for (int i = 0; i < row.Enemies.Num(); ++i)
		{
			AEnemy* enemy = row.Enemies[i];
			if (!enemy)
			{
				continue;
			}

			FVector Location = enemy->GetActorLocation();
			Location.Y = GetEnemyInitialHorizontalPosition(i, EnemiesIndentation) + HorizontalMovementShift;
			enemy->SetActorLocation(Location);
		}
	}
}

void UEnemyManager::OnEnemyHit(AEnemy* Target, AProjectile* Projectile, APlayerPawn* Ofender)
{
	Projectile->Destroy();

	// Update targets's health
	const float Damage = Target->MaxHealth / Target->GetHitTolerance();
	Target->Health = FMath::Floor(Target->Health - Damage);

	// Notify the Game Mode that the target was hit
	GameMode->OnEnemyHit(Target, Ofender);

	if (Target->Health <= 0.0f)
	{	// Notify the Game Mode that the target was killed
		GameMode->OnEnemyKilled(Target, Ofender);

		// The target is dead
		Target->Destroy();

		// Remove the dead enemy from its container row,
		// and calculate alive enemies
		int NumberAliveEnemies = 0;
		for (int i = 0; i < EnemyRows.Num(); ++i)
		{
			FEnemiesRow& Row = EnemyRows[i];
			for (int j = 0; j < Row.Enemies.Num(); ++j)
			{
				if (Row.Enemies[j])
				{
					if (Row.Enemies[j] == Target)
					{
						Row.Enemies[j] = nullptr;
						continue;
					}
					++NumberAliveEnemies;
				}
			}
		}

		// Are we done with the enemies?
		const auto AllEnemiesInRowAreDead = [](const FEnemiesRow& Row) {
			return std::all_of(Row.Enemies.begin(), Row.Enemies.end(), [](const AEnemy* Enemy) { return Enemy == nullptr; });
		};
		if (std::all_of(EnemyRows.begin(), EnemyRows.end(), AllEnemiesInRowAreDead))
		{
			GameMode->OnAllEnemiesKilled();
		}
		return;
	}

	// Update target's checkerboard look
	Target->UpdateMaterial();
}
