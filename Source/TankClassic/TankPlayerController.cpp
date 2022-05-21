#include "TankPlayerController.h"

//=====================================================================================================
// ����������� �����������
//=====================================================================================================
ATankPlayerController::ATankPlayerController(){}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
}

//=====================================================================================================
// ��������� �����������
//=====================================================================================================
void ATankPlayerController::SetupInputComponent(){
	Super::SetupInputComponent();

	//-----------------------------------------------------------------
	// ����������� ������ � ������� �������� ������-�����
	//-----------------------------------------------------------------
	InputComponent->BindAxis("MoveForward", this,	&ATankPlayerController::MoveForward);

	//-----------------------------------------------------------------
	// ����������� ������ � ������� �������� �������
	//-----------------------------------------------------------------
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
}

void ATankPlayerController::MoveForward(float AxisValue) { TankPawn->MoveForward(AxisValue); }
void ATankPlayerController::RotateRight(float AxisValue) { TankPawn->RotateRight(AxisValue); }

