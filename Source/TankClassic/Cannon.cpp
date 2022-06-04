//=====================================================================================================
#include "Cannon.h"

//#include "TankPlayerController.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogTMP_Tank, All, All);
//DEFINE_LOG_CATEGORY(LogTMP_Tank);

//=====================================================================================================
// ����������� �����
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
}

//=====================================================================================================
// ��������:
//=====================================================================================================
// �������
//=====================================================================================================
void ACannon::Fire(){
	if (!ReadyToFire)	{ return; }
	if (Ammo <= 0) { return; }

	ReadyToFire = false;

	UE_LOG(LogTemp, Warning, TEXT("PIU"));

	if (Type == ECannonType::FireProjectile) {
		//-----------------------------------------------------------------
		// ������� �� ����� ��� �������
		//-----------------------------------------------------------------
		GEngine->AddOnScreenDebugMessage(1, 3, FColor::Green, "Fire - projectile");
		//-----------------------------------------------------------------
		// ��������� ������
		//-----------------------------------------------------------------
		SpawnProjectile();
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 3, FColor::Green, "Fire - trace");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSecond(){
	if (!ReadyToFire) { return; }
	if (Ammo <= 0) { return; }
	
	ReadyToFire = false;
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, "Fire - trace");
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::AutoFire()
{
	if (!ReadyToFire) { return; }
	if (Ammo <= 0) { return; }

	GetWorld()->GetTimerManager().SetTimer(AutoFireTimerHandle, this, &ACannon::SpawnProjectile, 1 / (FireRate * ShootInFireRate), true);
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, "Auto Fire!");

	if (CountShoot > ShootInFireRate) {
		GetWorld()->GetTimerManager().ClearTimer(AutoFireTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("WE ARE HERE!!"));
		Reload();
	}

}

//=====================================================================================================
// ���������� � ��������
//=====================================================================================================
void ACannon::SpawnProjectile(){
	
	CountShoot++;
	UE_LOG(LogTemp, Warning, TEXT("CountShoot: %d"), CountShoot);
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	if (projectile) { projectile->Start(); }
}

//=====================================================================================================
// ���������� � ��������
//=====================================================================================================
bool ACannon::IsReadyToFire() {	return ReadyToFire; }

//=====================================================================================================
// �����������
//=====================================================================================================
void ACannon::Reload()
{	
	UE_LOG(LogTemp, Warning, TEXT("Ammo: %d"), Ammo);
	ReadyToFire = true;
	CountShoot = 0;
	Ammo--;
}

//=====================================================================================================
// � ������ ���� ������ �����������
//=====================================================================================================
void ACannon::BeginPlay(){
	Super::BeginPlay();
	Reload();
	Ammo = 10;
}