#include "Turret.h"
//======================================================================================================
// ???????????
//======================================================================================================
ATurret::ATurret() {
	//--------------------------------------------------------------------------------------------------
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret body"));
	RootComponent = BodyMesh;
	//--------------------------------------------------------------------------------------------------
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turretturret"));
	TurretMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);
	//--------------------------------------------------------------------------------------------------
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);
	//--------------------------------------------------------------------------------------------------
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(TurretMesh);

	//--------------------------------------------------------------------------------------------------
	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp) {TurretMesh->SetStaticMesh(turretMeshTemp);	}
	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp) {	BodyMesh->SetStaticMesh(bodyMeshTemp);}
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health	component"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATurret::DamageTaked);
}

//======================================================================================================
// ????? ??????? ? ?????? ????
//======================================================================================================
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint,	FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);
}

//======================================================================================================
//======================================================================================================
void ATurret::Die(){ Destroy();}

//======================================================================================================
//======================================================================================================
void ATurret::Destroyed() { if (Cannon) { Cannon->Destroy(); } }

//======================================================================================================
//======================================================================================================
void ATurret::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

//======================================================================================================
//======================================================================================================
void ATurret::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f "), *GetName(), DamageData.DamageValue);
}

//======================================================================================================
//======================================================================================================
void ATurret::Targeting()
{
	if (IsPlayerInRange())
	{
		RotateToPlayer();
	}
	if (CanFire() && Cannon && Cannon->IsReadyToFire())
	{
		Fire();
	}
}

//======================================================================================================
//======================================================================================================
void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TargetingSpeed));
}

//======================================================================================================
//======================================================================================================
bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

//======================================================================================================
//======================================================================================================
bool ATurret::CanFire()
{
	if (!IsPlayerSeen()) { return false; }

	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}

//======================================================================================================
//======================================================================================================
void ATurret::Fire() { if (Cannon) { Cannon->Fire(); } }

//======================================================================================================
//======================================================================================================
int32 ATurret::GetScoreOnDie() { return Score; }

FVector ATurret::GetEyesPosition() { return CannonSetupPoint->GetComponentLocation(); }

bool ATurret::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = GetEyesPosition();
	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(this);
	traceParams.bReturnPhysicalMaterial = false;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
	{
		if (hitResult.Actor.Get())
		{
			DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
			return hitResult.Actor.Get() == PlayerPawn;
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Cyan, false, 0.5f, 0, 10);
	return false;
}