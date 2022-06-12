#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::TakeDamage(FDamageData DamageData)
{
	//UE_LOG(LogTemp, Warning, TEXT("Inside UHealthComponent"));
	float takedDamageValue = DamageData.DamageValue;
	CurrentHealth -= takedDamageValue;
	if (CurrentHealth <= 0)
	{
		if (OnDie.IsBound()) {
			// ���� ���������� ������ �������� ���-�� ����� ������� ���� ���� � �������
			PlayerTakeScore(DamageData);
			OnDie.Broadcast(); 
		}
	}
	else
	{
		if (OnDamaged.IsBound()) { OnDamaged.Broadcast(takedDamageValue); }
	}
}

void UHealthComponent::PlayerTakeScore(FDamageData DamageData) {

	// �������� ����� ������
	APawn* tank = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATankPawn* MyTank = Cast<ATankPawn>(tank);
	
	// �������� � ����� �������� ����� �� ������
	MyTank->SetScore(DamageData.Score);
}

void UHealthComponent::AddHealth(float AddiditionalHealthValue)
{
	CurrentHealth += AddiditionalHealthValue;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}

float UHealthComponent::GetHealth() const { return CurrentHealth; }
float UHealthComponent::GetHealthState() const { return CurrentHealth / MaxHealth; }
