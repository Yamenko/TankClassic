#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "ExploseEffect.generated.h"

UCLASS()
class TANKCLASSIC_API AExploseEffect : public AActor
{
	GENERATED_BODY()
	
public:	

	AExploseEffect();
	//UFUNCTION()
	//void PlayEffect(FTransform HitPositionExploseEffect);

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* ShootEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioEffect;
};
