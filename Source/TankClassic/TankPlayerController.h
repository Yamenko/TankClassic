//=====================================================================================================
#pragma once
#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "TankPawn.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
//=====================================================================================================

//=====================================================================================================
UCLASS()
class TANKCLASSIC_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()	class ATankPawn* TankPawn;
	UPROPERTY()	FVector MousePos;

	//-----------------------------------------------------------------
	// Движение 
	//-----------------------------------------------------------------
	void MoveForward(float AxisValue);
	void MoveRight	(float AxisValue);
	void RotateRight(float AxisValue);

public:
	//-----------------------------------------------------------------
	// Конструктор
	//-----------------------------------------------------------------
	ATankPlayerController();

	//-----------------------------------------------------------------
	// Данные и функции
	//-----------------------------------------------------------------
	FVector GetMousePos() { return MousePos; };

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
};
