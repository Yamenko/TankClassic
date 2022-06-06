#pragma once
#include "CoreMinimal.h"
#include "TankPawn.h"
#include "Cannon.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "UObject/ObjectMacros.h"
#include "AmmoBox.generated.h"

UCLASS()
class TANKCLASSIC_API AAmmoBox : public AActor
{
	GENERATED_BODY()
public:
	AAmmoBox();
	//virtual void AAmmoBox::BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* AmmoBoxMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	TSubclassOf<ACannon> CannonClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 CountAmmo = 1;

	UFUNCTION()
	void OnMeshOverlapBegin(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);	

};
