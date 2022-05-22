//=====================================================================================================
#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//=====================================================================================================
// Конструктор класса ТАНК
//=====================================================================================================
ATankPawn::ATankPawn(){
	//-----------------------------------------------------------------
	// Обновлять каждый тик
	//-----------------------------------------------------------------
	PrimaryActorTick.bCanEverTick = true;

	//-----------------------------------------------------------------
	// Создание обхектов танка при спавне
	//-----------------------------------------------------------------
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	BodyMesh->SetupAttachment(RootComponent);
	//BodyMesh->SetSimulatePhysics(true);
	
	//-----------------------------------------------------------------
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(BodyMesh);
	//-----------------------------------------------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(TurretMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	//-----------------------------------------------------------------
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

//	Cannon

}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay(){
	Super::BeginPlay();
}

//=====================================================================================================
// Покадровое изменение (тик)
//=====================================================================================================
void ATankPawn::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//-----------------------------------------------------------------
	// Движение вперед-назад
	//-----------------------------------------------------------------
	FVector const CurrentPosition = GetActorLocation();
	FVector const ForwardVector	= GetActorForwardVector();
	FVector const RightVector = GetActorRightVector();
	FVector	NewPosition		=	CurrentPosition + \
								(ForwardVector * MoveSpeed *	TargetForwardAxisValue + \
								RightVector * MoveSpeed * TargetRightAxisValue) * DeltaTime;

	SetActorLocation(NewPosition, true);


	



	//-----------------------------------------------------------------
	// Движение повороты
	//-----------------------------------------------------------------
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += TargetRightRotateValue * DeltaTime;

	SetActorRotation(CurrentRotation, ETeleportType::None);
}

//=====================================================================================================
// Функции управления
//=====================================================================================================
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATankPawn::MoveForward	(float AxisValue)	{ TargetForwardAxisValue = AxisValue; }
void ATankPawn::MoveRight	(float AxisValue)	{ TargetRightAxisValue = AxisValue; }
void ATankPawn::RotateRight	(float AxisValue)	{ TargetRightRotateValue = AxisValue; }

