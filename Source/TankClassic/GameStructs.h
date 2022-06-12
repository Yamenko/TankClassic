//=====================================================================================================
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"
//=====================================================================================================
//=====================================================================================================

UENUM(BlueprintType)
enum class ECannonType : uint8 {
	FireProjectile	= 0 UMETA(DisplayName = "Use projectile"),
	FireTrace		= 1 UMETA(DisplayName = "Use trace")
};

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY()	float DamageValue;
	UPROPERTY()	AActor* Instigator;
	UPROPERTY()	AActor* DamageMaker;
	UPROPERTY() int32 Score;
};


//=====================================================================================================
//=====================================================================================================
UCLASS()
class TANKCLASSIC_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
//=====================================================================================================