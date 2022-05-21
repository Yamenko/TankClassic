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
	// Конструктор класса (базовый)
	//-----------------------------------------------------------------
	ATankPawn();

	//-----------------------------------------------------------------
	// Called every frame
	//-----------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------
	// Движение, ввод и контроллер
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
	// Меши и компоненты
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
	// Переменные
	//-----------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float MoveSpeed = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Speed")
	float RotationSpeed = 0.0f;

private:

};
//=====================================================================================================