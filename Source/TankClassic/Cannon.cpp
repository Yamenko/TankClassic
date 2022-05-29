//=====================================================================================================
#include "Cannon.h"
//#include "TankPlayerController.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogTMP_Tank, All, All);
//DEFINE_LOG_CATEGORY(LogTMP_Tank);

//=====================================================================================================
// Конструктор пушки
//=====================================================================================================
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	sceeneCpm->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

//=====================================================================================================
// Дейчтвия:
//=====================================================================================================
// Выстрел
//=====================================================================================================
void ACannon::Fire(){
	if (!ReadyToFire)	{ return; }
	if (Ammo <= 0) { return; }

	Ammo--;
	ReadyToFire = false;

	UE_LOG(LogTemp, Warning, TEXT("PIU"));

	if (Type == ECannonType::FireProjectile) {
		GEngine->AddOnScreenDebugMessage(10, 3, FColor::Green, "Fire - projectile");
	}
	else {
		GEngine->AddOnScreenDebugMessage(10, 3, FColor::Green, "Fire - trace");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSecond(){
	if (!ReadyToFire) { return; }
	if (Ammo <= 0) { return; }
	Ammo--;
	ReadyToFire = false;
	GEngine->AddOnScreenDebugMessage(11, 3, FColor::Red, "Fire - trace");
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::AutoFire()
{
	if (!ReadyToFire) { return; }
	if (Ammo <= 0) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Auto Fire:"));

	Fire();

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
	UE_LOG(LogTemp, Warning, TEXT("Ammo: %d"), Ammo);
	ReadyToFire = true;
}

//=====================================================================================================
// А начале игры делаем перезарядку
//=====================================================================================================
void ACannon::BeginPlay(){
	Super::BeginPlay();
	Reload();
	Ammo = 10;
}