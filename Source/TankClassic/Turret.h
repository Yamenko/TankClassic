#pragma once
#include "CoreMinimal.h"
#include "Cannon.h"
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "GameStructs.h"
#include "TankPawn.h"
#include "Turret.generated.h"


UCLASS()
class TANKCLASSIC_API ATurret : public AActor, public IDamageTaker
{
	GENERATED_BODY()
public:
	ATurret();
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()	void Die();
	UFUNCTION()	void DamageTaked(float DamageValue);
	UFUNCTION()	void TakeDamage(FDamageData DamageData);
	//UFUNCTION()	void PlayerTakeScore(FDamageData DamageData);
	UFUNCTION()	int32 GetScoreOnDie();
	UFUNCTION() FVector GetEyesPosition();
	UFUNCTION() bool IsPlayerSeen();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* HitCollider;
	UPROPERTY()	class ACannon* Cannon;
	UPROPERTY()	class APawn* PlayerPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float Accurency = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	int32 Score = 10;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
};
