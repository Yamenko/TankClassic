#include "TankAIController.h"

//=======================================================================================================================
//=======================================================================================================================
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector pawnLocation = TankPawn->GetActorLocation();
	MovementAccurency = TankPawn->GetMovementAccurency();
	TArray<FVector> points = TankPawn->GetPatrollingPoints();
	for (FVector point : points)
	{
		PatrollingPoints.Add(point + pawnLocation);
	}
	CurrentPatrolPointIndex = 0;
}

//=======================================================================================================================
//=======================================================================================================================
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TankPawn->MoveForward(1);
	Super::Tick(DeltaTime);
	TankPawn->MoveForward(1);
	float rotationValue = GetRotationgValue();
	TankPawn->RotateRight(rotationValue);
	Targeting();



	//FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
	//FVector pawnLocation = TankPawn->GetActorLocation();
	//if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurency)
	//{
	//	CurrentPatrolPointIndex++;
	//	if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
	//		CurrentPatrolPointIndex = 0;
	//}
	//FVector moveDirection = currentPoint - pawnLocation;
	//moveDirection.Normalize();
	//FVector forwardDirection = TankPawn->GetActorForwardVector();
	//FVector rightDirection = TankPawn->GetActorRightVector();
	//DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Green, false, 0.1f, 0, 5);

	//float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	//float rightAngle =	FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));
	//float rotationValue = 0;
	//if (forwardAngle > 5) { rotationValue = 1; }
	//if (rightAngle > 90) { rotationValue = -rotationValue; }
	////UE_LOG(LogTemp, Warning, TEXT("AI Rotation forwardAngle: %f rightAngle: %f rotationValue:% f"), forwardAngle, rightAngle, rotationValue);
	//TankPawn->RotateRight(rotationValue);
}

//=======================================================================================================================
//=======================================================================================================================
float ATankAIController::GetRotationgValue()
{
	FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurency)
	{
		CurrentPatrolPointIndex++;
		if (CurrentPatrolPointIndex >= PatrollingPoints.Num()) { CurrentPatrolPointIndex = 0; }
	}
	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();
	//DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Green, false, 0.1f, 0, 5);
	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));
	float rotationValue = 0;
	if (forwardAngle > 5) { rotationValue = 1; }
	if (rightAngle > 90) { rotationValue = -rotationValue; }
	return rotationValue;
}

//=======================================================================================================================
//=======================================================================================================================
void ATankAIController::Targeting()
{
	if (CanFire()) { Fire(); }
	else { RotateToPlayer(); }
}

//=======================================================================================================================
//=======================================================================================================================
void ATankAIController::RotateToPlayer()
{
	if (IsPlayerInRange()) { TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation()); }
}

//=======================================================================================================================
//=======================================================================================================================
bool ATankAIController::IsPlayerInRange()
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
}

//=======================================================================================================================
//=======================================================================================================================
bool ATankAIController::CanFire()
{
	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}

//=======================================================================================================================
//=======================================================================================================================
void ATankAIController::Fire(){ TankPawn->Fire(); }