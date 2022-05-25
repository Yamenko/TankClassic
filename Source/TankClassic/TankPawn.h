//=====================================================================================================
#pragma once
#include "CoreMinimal.h"
#include "Cannon.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "TankPawn.generated.h"
//=====================================================================================================
//=====================================================================================================

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class ATankPlayerController;
class ACannon;

//=====================================================================================================
//=====================================================================================================
UCLASS()
class TANKCLASSIC_API ATankPawn : public APawn
{ 
	GENERATED_BODY()
public:
	//-----------------------------------------------------------------
	// ����������� ������ (�������)
	//-----------------------------------------------------------------
	ATankPawn();

	//-----------------------------------------------------------------
	// Called every frame
	//-----------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------
	// ����������
	//-----------------------------------------------------------------
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()	void MoveForward(float AxisValue);
	UFUNCTION()	void MoveRight(float AxisValue);
	UFUNCTION()	void RotateRight(float AxisValue);
	UFUNCTION()	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools | dX Line trace")
	float dif_X_line = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools | dY Line trace")
	float dif_Y_line = 0.0f;

protected:
	//-----------------------------------------------------------------
	// Called when the game starts or when spawned
	//-----------------------------------------------------------------
	virtual void BeginPlay() override;
	void SetupCannon();

	UPROPERTY()	class ATankPlayerController* TankController;
	UPROPERTY() class ACannon* Cannon;

	//-----------------------------------------------------------------
	// ���� � ����������
	//-----------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	//UStaticMeshComponent* Cannon;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent * SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent * Camera;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
	TSubclassOf<ACannon> CannonClass;

	//-----------------------------------------------------------------
	// ����������
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

private:
	float TargetForwardAxisValue;
	float TargetRightAxisValue;
	float TargetRightRotateValue;
	float CurrentRightAxisValue;
};
//=====================================================================================================