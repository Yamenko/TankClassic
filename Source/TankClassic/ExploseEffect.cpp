#include "ExploseEffect.h"

AExploseEffect::AExploseEffect()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shoot effect"));
	ShootEffect->SetupAttachment(RootComponent);
	//ShootEffect->SetAutoActivate(false);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio effect"));
	AudioEffect->SetupAttachment(RootComponent);
	//AudioEffect->SetAutoActivate(false);
}

//void AExploseEffect::PlayEffect(FTransform HitPositionExploseEffect)
//{
//		ShootEffect->SetActive(true);
//		AudioEffect->SetActive(true);
//}

