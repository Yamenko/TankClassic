#include "TankFactory.h"

//=======================================================================================================================
ATankFactory::ATankFactory()
{
	PrimaryActorTick.bCanEverTick = false;
	//-------------------------------------------------------------------------------------------------------------------
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;
	//-------------------------------------------------------------------------------------------------------------------
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
	BuildingMesh->SetupAttachment(sceneComp);
	BuildingMesh->SetVisibility(true);
	
	BuildingMeshAfterDie = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh Die"));
	BuildingMeshAfterDie->SetupAttachment(sceneComp);
	BuildingMeshAfterDie->SetVisibility(false);
	//-------------------------------------------------------------------------------------------------------------------
	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setuppoint"));
	TankSpawnPoint->AttachToComponent(BuildingMesh, FAttachmentTransformRules::KeepRelativeTransform);
	//-------------------------------------------------------------------------------------------------------------------
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(sceneComp);
	//-------------------------------------------------------------------------------------------------------------------
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankFactory::DamageTaked);

	SpawnEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn effect"));
	SpawnEffect->SetupAttachment(sceneComp);
	SpawnEffect->SetAutoActivate(false);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio effect"));
	AudioEffect->SetupAttachment(sceneComp);
	AudioEffect->SetAutoActivate(false);
}
//=======================================================================================================================

//=======================================================================================================================
void ATankFactory::BeginPlay()
{
	Super::BeginPlay();
	
	if (LinkedMapLoader){ LinkedMapLoader->SetIsActivated(false); }
	
	isAlive = true;

	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this, &ATankFactory::SpawnNewTank, SpawnTankRate, true, SpawnTankRate);
}
//=======================================================================================================================

//=======================================================================================================================
void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}
//=======================================================================================================================

//=======================================================================================================================
void ATankFactory::Die()
{
	if (LinkedMapLoader) { 
		LinkedMapLoader->SetIsActivated(true); 
	}	
	isAlive = false;
	BuildingMesh->SetVisibility(false);
	BuildingMeshAfterDie->SetVisibility(true);
	//Destroy();
}
//=====================================================================================================aaaaaa==================

//=======================================================================================================================
void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}
//=======================================================================================================================

//=======================================================================================================================
void ATankFactory::SpawnNewTank()
{
	if (isAlive) {
		FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
		ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		newTank->SetPatrollingPoints(TankWayPoints);
		UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
		AudioEffect->Play();
		SpawnEffect->ActivateSystem();
	}
}
//=======================================================================================================================