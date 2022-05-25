//=====================================================================================================
#include "TankPlayerController.h"
//=====================================================================================================

//=====================================================================================================
// �������������� ���������� � ��������
//=====================================================================================================
DECLARE_LOG_CATEGORY_EXTERN(LogTMP_Mouse, All, All);
DEFINE_LOG_CATEGORY(LogTMP_Mouse);

//=====================================================================================================
// ����������� �����������
//=====================================================================================================
ATankPlayerController::ATankPlayerController(){}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	//-----------------------------------------------------------------
	// ����������� ��� ���� � ����������� (�������� ��������� �� ��� ����)
	//-----------------------------------------------------------------
	TankPawn = Cast<ATankPawn>(GetPawn());

	//-----------------------------------------------------------------
	// ��������� �����������
	//-----------------------------------------------------------------
	bShowMouseCursor = true; // ��������� �������
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//-----------------------------------------------------------------
	// ������ ��������� �����
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
// ��������� �����������
//=====================================================================================================
void ATankPlayerController::SetupInputComponent(){
	Super::SetupInputComponent();

	//-----------------------------------------------------------------
	// ����������� ������ � ������� �������� ������-�����
	//-----------------------------------------------------------------
	InputComponent->BindAxis("MoveForward", this,	&ATankPlayerController::MoveForward);

	//-----------------------------------------------------------------
	// ����������� ������ � ������� �������� ����-�����
	//-----------------------------------------------------------------
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveRight);

	//-----------------------------------------------------------------
	// ����������� ������ � ������� �������� �������
	//-----------------------------------------------------------------
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);

	//-----------------------------------------------------------------
	// ����������� ������ � ��������
	//-----------------------------------------------------------------
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
}


void ATankPlayerController::MoveForward(float AxisValue) { TankPawn->MoveForward(AxisValue); }
void ATankPlayerController::MoveRight(float AxisValue)	 { TankPawn->MoveRight(AxisValue);	 }
void ATankPlayerController::RotateRight(float AxisValue) { TankPawn->RotateRight(AxisValue); }
void ATankPlayerController::Fire()						 { TankPawn->Fire();}


