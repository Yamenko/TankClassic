#pragma once
#include "CoreMinimal.h"
#include "GameStructs.h"
#include "TankPawn.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKCLASSIC_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_EVENT(UHealthComponent, FOnDie)
	DECLARE_EVENT_OneParam(UHealthComponent, FOnHealthChanged, float)
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
	float MaxHealth = 5;
	
	UPROPERTY()
	float CurrentHealth;
public:
	FOnDie OnDie;
	FOnHealthChanged OnDamaged;
	UHealthComponent();
	void TakeDamage(FDamageData DamageData);
	void PlayerTakeScore(FDamageData DamageData);
	float GetHealth() const;
	float GetHealthState() const;
	void AddHealth(float AddiditionalHealthValue);
};
