// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Projectile.h"

namespace {
	constexpr float MAX_HEALTH = 100.0f;
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

	BoxCollider = this->FindComponentByClass<UStaticMeshComponent>();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);
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

		float damage;
		switch (Strength)
		{
		case EEnemyStrength::Weak:
			damage = MAX_HEALTH / 3.0f;
			break;
		case EEnemyStrength::Normal:
			damage = MAX_HEALTH / 5.0f;
			break;
		case EEnemyStrength::Strong:
		default:
			damage = MAX_HEALTH / 15.0f;
		}
		Health = FMath::Floor(Health - damage);
		if (Health <= 0.0f)
		{
			Destroy();
		}
	}
}
