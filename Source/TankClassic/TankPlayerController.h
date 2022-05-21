//=====================================================================================================
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPawn.h"
#include "TankPlayerController.generated.h"
//=====================================================================================================
//=====================================================================================================



//=====================================================================================================
//=====================================================================================================
UCLASS()
class TANKCLASSIC_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class ATankPawn* TankPawn;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);
	void RotateRight(float AxisValue);

public:
	ATankPlayerController();
};
