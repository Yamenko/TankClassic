#include "TankPlayerController.h"

//=====================================================================================================
// Конструктор контроллера
//=====================================================================================================
ATankPlayerController::ATankPlayerController(){}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
}

//=====================================================================================================
// Настройка контроллера
//=====================================================================================================
void ATankPlayerController::SetupInputComponent(){
	Super::SetupInputComponent();

	//-----------------------------------------------------------------
	// Привязываем кнопки к функции движения вперед-назад
	//-----------------------------------------------------------------
	InputComponent->BindAxis("MoveForward", this,	&ATankPlayerController::MoveForward);

	//-----------------------------------------------------------------
	// Привязываем кнопки к функции движения поворот
	//-----------------------------------------------------------------
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
}

void ATankPlayerController::MoveForward(float AxisValue) { TankPawn->MoveForward(AxisValue); }
void ATankPlayerController::RotateRight(float AxisValue) { TankPawn->RotateRight(AxisValue); }

