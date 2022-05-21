//=====================================================================================================
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"
//=====================================================================================================
//=====================================================================================================

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

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
	// ��������, ���� � ����������
	//-----------------------------------------------------------------
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float AxisValue);

protected:
	//-----------------------------------------------------------------
	// Called when the game starts or when spawned
	//-----------------------------------------------------------------
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------
	// ���� � ����������
	//-----------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Cannon;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent * SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent * Camera;

	//-----------------------------------------------------------------
	// ����������
	//-----------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float MoveSpeed = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float RotationSpeed = 0.0f;

private:

};
//=====================================================================================================