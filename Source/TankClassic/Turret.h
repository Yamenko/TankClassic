#pragma once
#include "CoreMinimal.h"
#include "Cannon.h"
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Turret.generated.h"


UCLASS()
class TANKCLASSIC_API ATurret : public AActor
{
	GENERATED_BODY()
public:
	ATurret();
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* HitCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	TSubclassOf<ACannon> CannonClass;
	UPROPERTY()
	ACannon* Cannon;
	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float Accurency = 10;
	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
};
