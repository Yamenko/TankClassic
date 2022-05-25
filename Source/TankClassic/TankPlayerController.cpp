//=====================================================================================================
#include "TankPlayerController.h"
//=====================================================================================================

//=====================================================================================================
// Декларирование переменных и макросов
//=====================================================================================================
DECLARE_LOG_CATEGORY_EXTERN(LogTMP_Mouse, All, All);
DEFINE_LOG_CATEGORY(LogTMP_Mouse);

//=====================================================================================================
// Конструктор контроллера
//=====================================================================================================
ATankPlayerController::ATankPlayerController(){}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	//-----------------------------------------------------------------
	// Привязываем наш танк к контроллеру (получаем указатель на наш танк)
	//-----------------------------------------------------------------
	TankPawn = Cast<ATankPawn>(GetPawn());

	//-----------------------------------------------------------------
	// Настройки контроллера
	//-----------------------------------------------------------------
	bShowMouseCursor = true; // включение курсора
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//-----------------------------------------------------------------
	// Расчет положения башни
	//-----------------------------------------------------------------
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	FVector pawnPos = TankPawn->GetActorLocation();
	MousePos.Z = pawnPos.Z;
	FVector dir = MousePos - pawnPos;
	dir.Normalize();
	MousePos = pawnPos + dir * 1000;

	DrawDebugLine(GetWorld(), pawnPos, MousePos, FColor::Green, false, 0.1f, 2, 5);

	//UE_LOG(LogTMP_Mouse, Warning, TEXT("Position Mouse: x = %f, y = %f, z = %f"), MousePos.X, MousePos.Y, MousePos.Z);
	//UE_LOG(LogTMP_Mouse, Warning, TEXT("Position PawnPos: x = %f, y = %f, z = %f"), pawnPos.X, pawnPos.Y, pawnPos.Z);
	//UE_LOG(LogTMP_Mouse, Warning, TEXT("Position DIR: x = %f, y = %f, z = %f"), dir.X, dir.Y, dir.Z);
	//UE_LOG(LogTMP_Mouse, Warning, TEXT("Position M_DIR: x = %f, y = %f, z = %f"), mouseDirection.X, mouseDirection.Y, mouseDirection.Z);
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
	// Привязываем кнопки к функции движения лево-право
	//-----------------------------------------------------------------
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveRight);

	//-----------------------------------------------------------------
	// Привязываем кнопки к функции движения поворот
	//-----------------------------------------------------------------
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);

	//-----------------------------------------------------------------
	// Привязываем кнопку к выстрелу
	//-----------------------------------------------------------------
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
}


void ATankPlayerController::MoveForward(float AxisValue) { TankPawn->MoveForward(AxisValue); }
void ATankPlayerController::MoveRight(float AxisValue)	 { TankPawn->MoveRight(AxisValue);	 }
void ATankPlayerController::RotateRight(float AxisValue) { TankPawn->RotateRight(AxisValue); }
void ATankPlayerController::Fire()						 { TankPawn->Fire();}


