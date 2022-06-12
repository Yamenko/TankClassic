#pragma once
#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "TankPawn.generated.h"
//=====================================================================================================
//=====================================================================================================

//class UStaticMeshComponent;
//class USpringArmComponent;
//class UCameraComponent;
//class ATankPlayerController;
//class ACannon;

//=====================================================================================================
//=====================================================================================================

UCLASS()
class TANKCLASSIC_API ATankPawn :  public APawn, public IDamageTaker
{
	GENERATED_BODY()
public:
	ATankPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------
	// Управление
	//-----------------------------------------------------------------
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()	void MoveForward(float AxisValue);
	UFUNCTION()	void MoveRight(float AxisValue);
	UFUNCTION()	void RotateRight(float AxisValue);
	UFUNCTION()	void Fire();
	UFUNCTION()	void FireSecond();
	UFUNCTION()	void AutoFire();
	UFUNCTION() void SetupCannon(TSubclassOf<ACannon> CannonType);
	UFUNCTION() void ChangeWeapon();

	UFUNCTION() ACannon* GetCannon();
	UFUNCTION()	void TakeDamage(FDamageData DamageData);
	UFUNCTION()	void SetScore(int32 TakeScore);

	UFUNCTION()	TArray<FVector> GetPatrollingPoints() { return PatrollingPoints; };
	UFUNCTION()	float GetMovementAccurency() { return MovementAccurency; };

	UFUNCTION()	FVector GetTurretForwardVector();
	UFUNCTION()	void RotateTurretTo(FVector TargetPosition);

	FVector GetEyesPosition();

protected:

	UFUNCTION()	void Die();
	UFUNCTION()	void DamageTaked(float DamageValue);

	UPROPERTY()	class ATankPlayerController* TankController;
	UPROPERTY() class ACannon* Cannon;

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	//-----------------------------------------------------------------
	// Меши и компоненты
	//-----------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
	TSubclassOf<ACannon> CannonClass;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* HitCollider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
	TArray<TSubclassOf<ACannon>> HaveCannons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<FVector> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params | Accurency")
	float MovementAccurency = 50;



	//-----------------------------------------------------------------
	// Переменные
	//-----------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float MoveSpeed = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float RotationSpeed = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float InterpolarKeyRotate = 0.01f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float InterpolarKeyMove = 0.01f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret	 | Speed")
	float TurretRotationInterpolationKey = 0.5f;

	int32 Score;

private:
	float TargetForwardAxisValue;
	float TargetRightAxisValue;
	float TargetRightRotateValue;
	float CurrentRightAxisValue;
};
//=====================================================================================================