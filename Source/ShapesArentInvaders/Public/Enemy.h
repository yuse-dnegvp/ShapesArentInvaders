// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UENUM()
enum class EEnemyStrength : uint8
{
	Weak,
	Normal,
	Strong,
	LAST_ELEMENT = Strong
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyStrength Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

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
