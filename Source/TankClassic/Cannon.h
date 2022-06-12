//=====================================================================================================
#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "Projectile.h"
#include "GameStructs.h"
#include "Logging/LogMacros.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#include "Templates/SubclassOf.h"
#include "Cannon.generated.h"
//=====================================================================================================
//=====================================================================================================
//class UArrowComponent;
class AProjectile;

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
	void SetAmmo(int32 CountTakeAmmo);

	ECannonType GetCannonType();
	ECannonType SetCannonType(ECannonType NewType);

	FTimerHandle ReloadTimerHandle;
	FTimerHandle AutoFireTimerHandle;

protected:
	bool ReadyToFire = false;
	virtual void BeginPlay() override;
	void SpawnProjectile();

	UPROPERTY()	class ATankPawn* TankPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent * CannonMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int ShootInFireRate = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireDamage = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int32 AmmoCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int32 CountProjectileAutoFire;
};
//=====================================================================================================
