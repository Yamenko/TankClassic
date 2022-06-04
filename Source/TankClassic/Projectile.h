#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Projectile.generated.h"

UCLASS()
class TANKCLASSIC_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	void Start();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage = 1;

	FTimerHandle MovementTimerHandle;

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
							class AActor* OtherActor,
							class UPrimitiveComponent* OtherComp, 
							int32 OtherBodyIndex, 
							bool bFromSweep, 
							const FHitResult& SweepResult);
	UFUNCTION()	void Move();	

};
