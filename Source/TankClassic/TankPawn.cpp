#include "TankPawn.h"
//=====================================================================================================

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
	RootComponent = BodyMesh;
	////-----------------------------------------------------------------
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(BodyMesh);
	//-----------------------------------------------------------------
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);
	////-----------------------------------------------------------------
	BodyMesh->OnComponentBeginOverlap.AddDynamic(this, &ATankPawn::OnMeshOverlapBegin);
	BodyMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	BodyMesh->SetGenerateOverlapEvents(true);
	////-----------------------------------------------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	//-----------------------------------------------------------------
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	//-----------------------------------------------------------------
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankPawn::DamageTaked);
	//-----------------------------------------------------------------
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

}

//=====================================================================================================
// Действия на старте
//=====================================================================================================
void ATankPawn::BeginPlay() {
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());
	//Score = 0;
	SetupCannon(CannonClass);
}

//=====================================================================================================
// Настройка пушки
//=====================================================================================================
void ATankPawn::SetupCannon(TSubclassOf<ACannon> CannonType) {

	if (Cannon) { Cannon->Destroy(); }
	if (CannonType) { CannonClass = CannonType; }
	//if (!HaveCannons.IndexOfByKey(*CannonClass)) { 
		HaveCannons.Push(*CannonClass);
	//} // Если такой пушки не было добавим ее в массив
	
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale); //     KeepRelativeTransform SnapToTargetNotIncludingScale
}

void ATankPawn::ChangeWeapon() {
	int IndexCannon = HaveCannons.Num(); // Находим элемент того что сейчас установлено

	UE_LOG(LogTemp, Warning, TEXT("Index %d."), IndexCannon);
	//if (HaveCannons.IsValidIndex(++IndexCannon)) { SetupCannon(HaveCannons[IndexCannon]); }
	//else { SetupCannon(HaveCannons[0]); }
}

ACannon* ATankPawn::GetCannon(){ return Cannon;}

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

//=====================================================================================================
// Выстрел
//=====================================================================================================
void ATankPawn::Fire() { if (Cannon) { Cannon->Fire(); } }
void ATankPawn::FireSecond() { if (Cannon) { Cannon->FireSecond(); } }
void ATankPawn::AutoFire() { if (Cannon) { Cannon->AutoFire(); } }

//=====================================================================================================
// Пересечение
//=====================================================================================================
void ATankPawn::OnMeshOverlapBegin(
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

void ATankPawn::TakeDamage(FDamageData DamageData){	HealthComponent->TakeDamage(DamageData);}

void ATankPawn::SetScore(int32 TakeScore) {	
	Score += TakeScore;
	UE_LOG(LogTemp, Warning, TEXT("TANK take scores %d, New score: %d."), TakeScore, Score);
}

void ATankPawn::Die(){ Destroy();}
void ATankPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s taked damage:%f Health:%f"), *GetName(),	DamageValue, HealthComponent->GetHealth());
}