//=====================================================================================================
#include "TankPawn.h"
//=====================================================================================================

//=====================================================================================================
// Декларирование переменных и макросов
//=====================================================================================================
DECLARE_LOG_CATEGORY_EXTERN(LogTMP_Tank, All, All);
DEFINE_LOG_CATEGORY(LogTMP_Tank);

// Called when the game starts or when spawned
void ATankPawn::BeginPlay(){
	Super::BeginPlay();

	TankController = Cast<ATankPlayerController>(GetController());

}

//=====================================================================================================
// Конструктор класса ТАНК
//=====================================================================================================
ATankPawn::ATankPawn(){
	//-----------------------------------------------------------------
	// Обновлять каждый тик чтобы можно было двигать танк
	//-----------------------------------------------------------------
	PrimaryActorTick.bCanEverTick = true;

	//-----------------------------------------------------------------
	// Создание объектов танка при спавне
	//-----------------------------------------------------------------
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	BodyMesh->SetupAttachment(RootComponent);
	//RootComponent = BodyMesh;
	
	//-----------------------------------------------------------------
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(BodyMesh);
	//-----------------------------------------------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	//-----------------------------------------------------------------
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//	Cannon
}

//=====================================================================================================
// Покадровое изменение (тик) для движения
//=====================================================================================================
void ATankPawn::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//-----------------------------------------------------------------
	// Движение вперед-назад
	//-----------------------------------------------------------------
	FVector const CurrentPosition = GetActorLocation();
	FVector const ForwardVector	= GetActorForwardVector();
	FVector const RightVector = GetActorRightVector();
	FVector	const NewPosition =	CurrentPosition + \
								(ForwardVector * MoveSpeed *	TargetForwardAxisValue + \
								RightVector * MoveSpeed * TargetRightAxisValue) * DeltaTime;

	SetActorLocation(NewPosition, true);

	//-----------------------------------------------------------------
	// Движение повороты
	//-----------------------------------------------------------------
	FRotator CurrentRotation = GetActorRotation();
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, TargetRightRotateValue, InterpolarKeyRotate);
	CurrentRotation.Yaw += RotationSpeed * CurrentRightAxisValue * DeltaTime;
	FRotator NewRotation = FRotator(0, CurrentRotation.Yaw, 0);

	SetActorRotation(NewRotation);

	//-----------------------------------------------------------------
	// Поворот башни
	//-----------------------------------------------------------------
	if (TankController)
	{
		FVector mousePos = TankController->GetMousePos();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
		FRotator currRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = currRotation.Pitch;
		targetRotation.Roll = currRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
	}

	//-----------------------------------------------------------------
	// Логи (вывод сообщений)
	//-----------------------------------------------------------------
	// UE_LOG(LogTMP_Tank, Warning, TEXT("Position tank: x = %00.00f, y = %00.00f, z = %00.00f"), NewPosition.X, NewPosition.Y, NewPosition.Z);
}

//=====================================================================================================
// Функции управления
//=====================================================================================================
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){Super::SetupPlayerInputComponent(PlayerInputComponent);}
void ATankPawn::MoveForward				 (float AxisValue)						{ TargetForwardAxisValue = AxisValue; }
void ATankPawn::MoveRight				 (float AxisValue)						{ TargetRightAxisValue = AxisValue; }
void ATankPawn::RotateRight				 (float AxisValue)						{ TargetRightRotateValue = AxisValue; }

