#include "BlankOfTechniques.h"

//=====================================================================================================
// Конструктор класса ТАНК
//=====================================================================================================
ABlankOfTechniques::ABlankOfTechniques() {
	//-----------------------------------------------------------------
	// Создание объектов и привязка
	//-----------------------------------------------------------------
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = BodyMesh;
	//-----------------------------------------------------------------
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(BodyMesh);
	//-----------------------------------------------------------------
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);
	//-----------------------------------------------------------------
	BodyMesh->OnComponentBeginOverlap.AddDynamic(this, &ABlankOfTechniques::OnMeshOverlapBegin);
	BodyMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	BodyMesh->SetGenerateOverlapEvents(true);
}

void ABlankOfTechniques::BeginPlay()
{
	Super::BeginPlay();
}

//=====================================================================================================
// Покадровое изменение (тик) для движения
//=====================================================================================================
void ABlankOfTechniques::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);

	////-----------------------------------------------------------------
	//// Движение вперед-назад
	////-----------------------------------------------------------------
	//FVector const CurrentPosition = GetActorLocation();
	//FVector const ForwardVector = GetActorForwardVector();
	//FVector const RightVector = GetActorRightVector();
	//FVector	const NewPosition = CurrentPosition + \
	//	(ForwardVector * MoveSpeed * TargetForwardAxisValue + \
	//		RightVector * MoveSpeed * TargetRightAxisValue) * DeltaTime;

	//SetActorLocation(NewPosition, true);

	////-----------------------------------------------------------------
	//// Движение повороты
	////-----------------------------------------------------------------
	//FRotator CurrentRotation = GetActorRotation();
	//CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, TargetRightRotateValue, InterpolarKeyRotate);
	//CurrentRotation.Yaw += RotationSpeed * CurrentRightAxisValue * DeltaTime;
	//FRotator NewRotation = FRotator(0, CurrentRotation.Yaw, 0);

	//SetActorRotation(NewRotation);

	////-----------------------------------------------------------------
	//// Поворот башни
	////-----------------------------------------------------------------
	//if (TankController)
	//{
	//	FVector mousePos = TankController->GetMousePos();
	//	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
	//	FRotator currRotation = TurretMesh->GetComponentRotation();
	//	targetRotation.Pitch = currRotation.Pitch;
	//	targetRotation.Roll = currRotation.Roll;
	//	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
	//}
}


void ABlankOfTechniques::Destroyed()
{
	Super::Destroyed();
}

//=====================================================================================================
// Пересечение
//=====================================================================================================
void ABlankOfTechniques::OnMeshOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("TANK %s collided with %s. "), *GetName(), *OtherActor->GetName());

	/*OtherActor->Destroy();
	Destroy();*/

}