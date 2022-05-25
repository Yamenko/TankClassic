//=====================================================================================================
#include "Cannon.h"

//=====================================================================================================
// ����������� �����
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
// ��������:
//=====================================================================================================
// �������
//=====================================================================================================
void ACannon::Fire(){
	if (!ReadyToFire)	{ return; }

	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile) {
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
	}
	else {
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this,	&ACannon::Reload, 1 / FireRate, false);
}

//=====================================================================================================
// ���������� � ��������
//=====================================================================================================
bool ACannon::IsReadyToFire() {	return ReadyToFire; }

//=====================================================================================================
// �����������
//=====================================================================================================
void ACannon::Reload(){ ReadyToFire = true;}

//=====================================================================================================
// � ������ ���� ������ �����������
//=====================================================================================================
void ACannon::BeginPlay(){
	Super::BeginPlay();
	Reload();
}
//=====================================================================================================