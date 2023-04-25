// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Projectile.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BOOM!"));
		projectile->Destroy();
		Destroy();
	}
}
