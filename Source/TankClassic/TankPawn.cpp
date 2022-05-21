//=====================================================================================================
#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//=====================================================================================================
// ����������� ������ ����
//=====================================================================================================
ATankPawn::ATankPawn(){
	//-----------------------------------------------------------------
	// ��������� ������ ���
	//-----------------------------------------------------------------
	PrimaryActorTick.bCanEverTick = true;

	//-----------------------------------------------------------------
	// �������� �������� ����� ��� ������
	//-----------------------------------------------------------------
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	BodyMesh->SetupAttachment(RootComponent);
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
// ���������� ��������� (���)
//=====================================================================================================
void ATankPawn::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	//-----------------------------------------------------------------
	// �������� ������-�����
	//-----------------------------------------------------------------
	FVector const CurrentPosition = GetActorLocation();
	FVector const ForwardVector	= GetActorForwardVector();
	FVector	NewPosition		= CurrentPosition + ForwardVector * MoveSpeed *	TargetForwardAxisValue * DeltaTime;

	SetActorLocation(NewPosition, true);

	//-----------------------------------------------------------------
	// �������� ��������
	//-----------------------------------------------------------------
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += TargetRightAxisValue * DeltaTime;

	SetActorRotation(CurrentRotation, ETeleportType::None);
}

//=====================================================================================================
// ������� ����������
//=====================================================================================================
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATankPawn::MoveForward(float AxisValue)	{ TargetForwardAxisValue = AxisValue; }
void ATankPawn::RotateRight(float AxisValue)	{ TargetRightAxisValue = AxisValue; }
