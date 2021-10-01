// Oh, boy. Here we go!


#include "EnemyShipsRegular.h"

AEnemyShipsRegular::AEnemyShipsRegular()
{

}

void AEnemyShipsRegular::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyShipsRegular::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunStates(STATE);

	DoTimers(DeltaTime);
}

void AEnemyShipsRegular::RunStates(int Value)
{
	Super::RunStates(Value);
	switch (Value)
	{
			// Idle
		case 0:
		{
			if (InLineOfSight(GetPlayerLocation(), true) && !bFoundPlayer)
			{
				bFoundPlayer = true;
				FoundPlayer();
			}
			break;
		}
		// Patrol
		case 1:
		{
			if (InLineOfSight(GetPlayerLocation(), true) && !bFoundPlayer)
			{
				bFoundPlayer = true;
				FoundPlayer();
			}
			break;
		}
		// Chase
		case 2:
		{
			bInSight = InLineOfSight(GetPlayerLocation());
			RotateTowardsPlayer();
			break;
		}
		// Stand Ground
		case 3:
		{
			bInSight = InLineOfSight(GetPlayerLocation());
			RotateTowardsPlayer();
			break;
		}
		// Flee
		case 4:
		{
			break;
		}
	}
}

int AEnemyShipsRegular::SetState(int Value)
{
	Super::SetState(Value);
	//if (STATE == Value)
		//return -1;

	int Previous = Value;

	CancelMovement();

	switch (Value)
	{
		//Idle
		case 0:
		{
			STATE = IDLE;
			bFoundPlayer = false;
			Acceptance = AcceptanceLost;
			break;
		}
		// Patrol
		case 1:
		{
			STATE = PATROL;
			FVector Loc = GetPlayerLocation();
			Loc.X += FMath::RandRange(-PatrolRandomLocation.X, PatrolRandomLocation.X);
			Loc.Y += FMath::RandRange(-PatrolRandomLocation.Y, PatrolRandomLocation.Y);
			TargetLocation = Loc;
			TargetActor = GetWorld()->GetFirstPlayerController()->GetPawn();
			Acceptance = AcceptanceLost;
			bFoundPlayer = false;
			break;
		}
		// Chase
		case 2:
		{
			STATE = CHASE;
			TargetActor = GetWorld()->GetFirstPlayerController()->GetPawn();
			TargetLocation = GetPlayerLocation();
			bFoundPlayer = true;
			Acceptance = AcceptanceFound;
			break;
		}
		// Stand ground
		case 3:
		{
			STATE = STANDGROUND;
			TargetActor = GetWorld()->GetFirstPlayerController()->GetPawn();
			TargetLocation = GetPlayerLocation();
			bFoundPlayer = true;
			Acceptance = AcceptanceFound;
			break;
		}
		// Flee
		case 4:
		{
			STATE = FLEE;
			TargetActor = GetWorld()->GetFirstPlayerController()->GetPawn();
			Acceptance = AcceptanceLost;
			break;
		}
	}
	OnStateChanged();
	return Value;
}
