#include "Projectile.h"

//=====================================================================================================
// ����������� ������ ������
//=====================================================================================================
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);	
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	ProjectileMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	ProjectileMesh->SetGenerateOverlapEvents(true);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
}

//=====================================================================================================
// ������� ������ ������ �������
//=====================================================================================================
void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

//=====================================================================================================
// ������� ������ �������
//=====================================================================================================
void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

//=====================================================================================================
// ������� �������������� ������� � ���������
//=====================================================================================================
void AProjectile::OnMeshOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("NEW Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;

			//�������� ���-�� ����� ������� ���� � ������ � ���������� � ���������
			ATurret* turret = Cast<ATurret>(OtherActor); 
			if (turret) { damageData.Score = turret->GetScoreOnDie(); }
			else { damageData.Score = 0; }
			damageTakerActor->TakeDamage(damageData);

		}
		else
		{
			//OtherActor->Destroy();
		}
		Destroy();
	}




	
	//UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	//OtherActor->Destroy();
	//Destroy();

}