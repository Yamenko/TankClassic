#include "AmmoBox.h"

AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	AmmoBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoBoxMesh"));
	AmmoBoxMesh->SetupAttachment(RootComponent);

	AmmoBoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin); //AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin)
	AmmoBoxMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
	AmmoBoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // ECollisionEnabled::QueryAndPhysics
	AmmoBoxMesh->SetGenerateOverlapEvents(true);
};

//void AAmmoBox::BeginPlay(){	Super::BeginPlay();}

void AAmmoBox::OnMeshOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BOX %s collided with %s. "), *GetName(), *OtherActor->GetName());
	ATankPawn* Tank = Cast<ATankPawn>(OtherActor);
	if (Tank) {	
		Tank->GetCannon()->SetAmmo(CountAmmo);
		Tank->SetupCannon(CannonClass);
	}
	Destroy();
};


