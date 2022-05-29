//=====================================================================================================
#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "Logging/LogMacros.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Cannon.generated.h"
//=====================================================================================================
//=====================================================================================================
class UArrowComponent;


//=====================================================================================================
//=====================================================================================================

UCLASS()
class TANKCLASSIC_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	

	ACannon();
	void Fire();
	void FireSecond();
	void AutoFire();
	bool IsReadyToFire();
	void Reload();

protected:
	bool ReadyToFire = false;
	virtual void BeginPlay() override;

	UPROPERTY()	class ATankPawn* TankPawn;

	FTimerHandle ReloadTimerHandle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent * Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireDamage = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;

private:

	int Ammo;
};
//=====================================================================================================
