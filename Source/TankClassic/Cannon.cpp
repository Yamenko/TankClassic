//=====================================================================================================
#include "Cannon.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogTMP_Tank, All, All);
//DEFINE_LOG_CATEGORY(LogTMP_Tank);

//=====================================================================================================
// Конструктор пушки
//=====================================================================================================
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	CannonMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shoot effect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio effect"));
	AudioEffect->SetupAttachment(CannonMesh);
}

//=====================================================================================================
// Действия:
//=====================================================================================================
// Выстрел
//=====================================================================================================
void ACannon::Fire(){
	if (!ReadyToFire || AmmoCount <= 0)	{ return; }

	ReadyToFire = false;

	ShootEffect->ActivateSystem();
	AudioEffect->Play();


	if (Type == ECannonType::FireProjectile){
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
		FTransform projectileTransform(ProjectileSpawnPoint->GetComponentRotation(), ProjectileSpawnPoint->GetComponentLocation(), FVector(1));
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		
		if (projectile)	{ projectile->Start();}
	}
	else {
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
		FHitResult hitResult;
		FCollisionQueryParams traceParams =	FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;
		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
		
		if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end,	ECollisionChannel::ECC_Visibility, traceParams)){
			DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);
			
			
			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(hitResult.Actor.Get());
			if (damageTakerActor) {
				FDamageData damageData;
				damageData.DamageValue = FireDamage;
				damageData.DamageMaker = this;
				damageTakerActor->TakeDamage(damageData);
				UE_LOG(LogTemp, Warning, TEXT("damage by trace."));
			}
		}
		else { DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);}
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1 / FireRate, false);
}

//=====================================================================================================
//=====================================================================================================
void ACannon::FireSecond(){
	if (!ReadyToFire || AmmoCount <= 0) { return; }
	
	ReadyToFire = false;
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, "Fire - trace");
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

//=====================================================================================================
//=====================================================================================================
void ACannon::AutoFire()
{
	if (!ReadyToFire || AmmoCount <= 0) { return; }

	ReadyToFire = false;

	GetWorld()->GetTimerManager().SetTimer(AutoFireTimerHandle, this, &ACannon::SpawnProjectile, 1 / (FireRate * ShootInFireRate), true);
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, "Auto Fire!");
	Reload();
}

//=====================================================================================================
// Готовность к стрельбе
//=====================================================================================================
void ACannon::SpawnProjectile()
{
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	if (projectile) { 
		projectile->Start(); 
		CountProjectileAutoFire++;
	}
	if (CountProjectileAutoFire >= 3) { GetWorld()->GetTimerManager().ClearTimer(AutoFireTimerHandle); }
}

//=====================================================================================================
// Готовность к стрельбе
//=====================================================================================================
bool ACannon::IsReadyToFire() {	return ReadyToFire; }

//=====================================================================================================
// Перезарядка
//=====================================================================================================
void ACannon::Reload()
{	
	UE_LOG(LogTemp, Warning, TEXT("Ammo: %d"), AmmoCount);
	CountProjectileAutoFire = 0;
	ReadyToFire = true;
	AmmoCount--;
}

//=====================================================================================================
// Получение патронов
//=====================================================================================================
void ACannon::SetAmmo(int32 CountTakeAmmo){	AmmoCount += CountTakeAmmo;}

//=====================================================================================================
// Возвращаем тип пушки
//=====================================================================================================
ECannonType ACannon::GetCannonType() {	return ACannon::Type; }
//ECannonType ACannon::SetCannonType(ECannonType NewType) { ACannon::Type = NewType; }

//=====================================================================================================
// В начале игры делаем перезарядку
//=====================================================================================================
void ACannon::BeginPlay(){
	Super::BeginPlay();
	Reload();
	AmmoCount = 10;
}