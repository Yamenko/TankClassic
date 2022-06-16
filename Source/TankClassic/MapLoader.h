#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MapLoader.generated.h"
UCLASS()
class TANKCLASSIC_API AMapLoader : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent * GatesMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* TriggerCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* ActivatedLight;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* DeactivatedLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
	FName LoadLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level loading params")
	bool IsActivated = false;
public:

	AMapLoader();
	void SetIsActivated(bool NewIsActivated);
protected:

	virtual void BeginPlay() override;
	void SetActiveLights();
	UFUNCTION()	void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, 
		AActor*	OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep,
		const FHitResult& SweepResult);
};
