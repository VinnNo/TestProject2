// Oh, boy. Here we go!


#include "EnemyBossShipA.h"
#include "GameFramework/RotatingMovementComponent.h"

AEnemyBossShipA::AEnemyBossShipA()
{
	// Creation Rotation
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	//RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(this, TEXT("RotatingMovement"));
	RotatingMovement->SetUpdatedComponent(RootComponent);
	RotatingMovement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);

	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyBossShipA::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBossShipA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunStates(STATE);

}

int AEnemyBossShipA::SetState(int Value)
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
			FRotator RotationalSpeed;

			if (FMath::RandRange(-10.0f, 10.0f) > 0.0f)
			{
				RotDir = 1.0f;
			}
			else
			{
				RotDir = -1.0f;
			}

			RotationalSpeed.Yaw = (RotSpeed * RotDir);

			if (IsValid(RotatingMovement))
			{
				RotatingMovement->RotationRate = RotationalSpeed;
			}
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

void AEnemyBossShipA::RunStates(int Value)
{
	Super::RunStates(Value);
	switch (Value)
	{
		// Spin
		case 0:
		{
			//RotateTowardsPlayer();

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
