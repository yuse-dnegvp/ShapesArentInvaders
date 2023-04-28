// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/SparseDelegate.h"
#include "Enemy.generated.h"

class AEnemy;
class AProjectile;
class UStaticMeshComponent;

UENUM()
enum class EEnemyStrength : uint8
{
	Weak,
	Normal,
	Strong,
	LAST_ELEMENT = Strong
};

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FEnemyHitSignature, AEnemy, OnHit, AEnemy*, Target, AProjectile*, Projectile);

UCLASS()
class SHAPESARENTINVADERS_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateMaterial();

	// Number of hits the Enemy can stand before it' dies's being killed
	int GetHitTolerance() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyStrength Strength;

	// Event called when this enemy is being hit
	UPROPERTY(BlueprintAssignable, Category = "Collision")
	FEnemyHitSignature OnHit;

private:
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BoxStaticMesh = nullptr;

	UMaterialInstanceDynamic* ChecherboardMaterial = nullptr;
};
