#include "Projectile.h"

//=====================================================================================================
// Конструктор класса Снаряд
//=====================================================================================================
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	


}

//=====================================================================================================
// Функция начала спавна снаряда
//=====================================================================================================
void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

//=====================================================================================================
// Функция полета снаряда
//=====================================================================================================
void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

//=====================================================================================================
// Функция взаимодействия снаряда с объектами
//=====================================================================================================
void AProjectile::OnMeshOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	OtherActor->Destroy();
	Destroy();

}