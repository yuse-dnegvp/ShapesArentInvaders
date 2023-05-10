// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Projectile.h"
#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

namespace {
	constexpr int CHECKERBOARD_NUMBER_SQUARES = 2;
}

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100.0f;
	Health = MaxHealth;
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
	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	if (Projectile)
	{
		auto Ofender = Cast<APlayerPawn>(Projectile->GetInstigator());
		OnHit.Broadcast(this, Projectile, Ofender);
	}
}

void AEnemy::UpdateMaterial()
{
	const float UVMultiplier = FMath::CeilToFloat(Health / 100.0f * GetHitTolerance()) / CHECKERBOARD_NUMBER_SQUARES;
	ChecherboardMaterial->SetScalarParameterValue(FName(TEXT("UVMultiplier")), UVMultiplier);
}

int AEnemy::GetHitTolerance() const
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
