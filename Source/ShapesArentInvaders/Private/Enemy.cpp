// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Projectile.h"
#include "Materials/MaterialInstanceConstant.h"

namespace {
	constexpr float MAX_HEALTH = 100.0f;
	constexpr int CHECKERBOARD_NUMBER_SQUARES = 2;
	constexpr float CHECKERBOARD_TEXTURE_NUMBER_QUARES = 2.0f;

	constexpr int GetNumberHitsBeforeDeath(EEnemyStrength Strength)
	{
		switch (Strength)
		{
		case EEnemyStrength::Weak:
			return 3;
		case EEnemyStrength::Normal:
			return 5;
		case EEnemyStrength::Strong:
		default:
			return 15;
		}
	}
}

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = MAX_HEALTH;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	BoxStaticMesh = this->FindComponentByClass<UStaticMeshComponent>();
	BoxStaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);

	ChecherboardMaterial = UMaterialInstanceDynamic::Create(BoxStaticMesh->GetMaterial(0), this);
	BoxStaticMesh->SetMaterial(0, ChecherboardMaterial);

	UpdateMaterial();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::OnCollision(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& Hit)
{
	AProjectile* projectile = Cast<AProjectile>(OtherActor);
	if (projectile)
	{
		projectile->Destroy();

		const int NumberHits = GetNumberHitsBeforeDeath(Strength);
		const float Damage = MAX_HEALTH / NumberHits;
		Health = FMath::Floor(Health - Damage);

		if (Health <= 0.0f)
		{
			Destroy();
			return;
		}

		UpdateMaterial();
	}
}

void AEnemy::UpdateMaterial()
{
	const int NumberHits = GetNumberHitsBeforeDeath(Strength);
	const float UVMultiplier = FMath::CeilToFloat(Health / 100.0f * NumberHits) / CHECKERBOARD_NUMBER_SQUARES;
	ChecherboardMaterial->SetScalarParameterValue(FName(TEXT("UVMultiplier")), UVMultiplier);
}
