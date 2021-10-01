// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShipBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"


// Sets default values
AEnemyShipBase::AEnemyShipBase()
{
	ShipSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ShipSpringArm"));
	ShipSpringArm->SetupAttachment(RootComponent);
	ShipSpringArm->TargetArmLength = 20.0f;
	ShipSpringArm->bUsePawnControlRotation = true;
	ShipSpringArm->bEnableCameraLag = true;
	ShipSpringArm->bEnableCameraRotationLag = true;
	ShipSpringArm->CameraLagSpeed = 0.5f;
	ShipSpringArm->CameraRotationLagSpeed = 3.0f;
	ShipSpringArm->CameraLagMaxDistance = 20.0f;

	// Ship mesh
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMeshComponent"));
	ShipMeshComponent->SetupAttachment(ShipSpringArm, USpringArmComponent::SocketName);
	//ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	Sight = CreateDefaultSubobject<USphereComponent>(TEXT("Sight"));
	Sight->SetupAttachment(RootComponent);
	Sight->SetSphereRadius(2000.0f, false);

	// Movement Defaults
	GetCharacterMovement()->MaxAcceleration = 200.0f;
	GetCharacterMovement()->MaxStepHeight = 0.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(0.0f);
	GetCharacterMovement()->GroundFriction = 0.1f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 0.1f;

	// Capsule Stuff
	GetCapsuleComponent()->SetCapsuleHalfHeight(225.0f);
	GetCapsuleComponent()->SetCapsuleRadius(170.0f);


 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyShipBase::BeginPlay()
{
	Super::BeginPlay();
	AcceptanceFound = (Sight->GetScaledSphereRadius() / 2);
	if (GetWorld() != nullptr)
	{
		if (GetWorld()->GetFirstPlayerController()->GetPawn() != nullptr)
		{
			Player = GetWorld()->GetFirstPlayerController()->GetPawn();
		}
	}

	if (IsValid(Player))
	{
		DistanceToPlayer = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	}
}

// Called every frame
void AEnemyShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//RunStates(STATE);

	//DoTimers(DeltaTime);
}

// Called to bind functionality to input
void AEnemyShipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FRotator AEnemyShipBase::GetTargetRotation(FVector Target)
{
	FVector Current = GetActorLocation();

	FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(Current, Target);

	TargetRot.Roll = 0.0f;
	TargetRot.Pitch = 0.0f;
	return TargetRot;
}

void AEnemyShipBase::CancelMovement()
{
	FVector StoredVelocity = GetMovementComponent()->Velocity;
	if (StoredVelocity != FVector(0.0f, 0.0f, 0.0f))
	{
		GetCharacterMovement()->StopActiveMovement();
		GetMovementComponent()->Velocity = StoredVelocity;
	}
}

int AEnemyShipBase::SetState(int Value)
{
	/*
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
	*/
	return Value;
}

void AEnemyShipBase::RunStates(int Value)
{
	/*
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
	*/
}


void AEnemyShipBase::RotateTowardsPlayer()
{
	if (!bShouldRotate)
	{
		return;
	}
	SetActorRotation(GetTargetRotation(GetPlayerLocation()));
}

FVector AEnemyShipBase::GetPlayerLocation()
{
	if (GetWorld() != nullptr)
	{
		Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	FVector Loc;
	if (Player != nullptr)
	{
		Loc = Player->GetActorLocation();
	}
	else
	{
		Player = this;
	}
	return Loc;
}

void AEnemyShipBase::StartPatrolTimer(bool bReset)
{
	if (bPatrolTimerActive)
	{
		if (bReset)
		{
			PatrolTimerCurrent = 0.0f;
			return;
		}
	}
	else
	{
		bPatrolTimerActive = true;
		return;
	}
}

void AEnemyShipBase::DoTimers(float Delta)
{

	if (bPatrolTimerActive)
	{
		if (PatrolTimerCurrent < PatrolTimerMax)
		{
			PatrolTimerCurrent += 1 * Delta;
		}
		else
		{
			bPatrolTimerActive = false;
			PatrolTimerCurrent = 0.0f;
			PatrolTimerUp();
		}
	}
}

void AEnemyShipBase::SpawnLoot(bool &bComplete)
{
	int TempValue = LootValue;
	int TempSpawn = LootSpawnCount;

	while ( (TempValue > 0) && (TempSpawn > 0) )
	{
		float RandomNumber = FMath::RandRange(1.0f, 100.0f);
		if (RandomNumber > 70)
		{
			if (--TempValue > 300)
			{
				OnGemSpawn.Broadcast(3);
				OnGemSpawn.Broadcast(3);
				TempValue = FMath::Max( 0, ((TempValue / 4) * 3) );
				TempSpawn -= 3;
			}
			else if (--TempValue > 150)
			{
				OnGemSpawn.Broadcast(3);
				OnGemSpawn.Broadcast(2);
				OnGemSpawn.Broadcast(1);
				TempValue = FMath::Max(0, ((TempValue / 3) * 2));
				TempSpawn -= 2;
			}
			else
			{
				--TempValue;
				OnGemSpawn.Broadcast(2);
				OnGemSpawn.Broadcast(1);
				TempValue = FMath::Max(0, ((TempValue / 3) * 2));
				TempSpawn -= 1;
			}
		}
		else if (RandomNumber > 50)
		{
			if (--TempValue > 250)
			{
				OnGemSpawn.Broadcast(3);
				OnGemSpawn.Broadcast(2);
				TempValue = FMath::Max(0, ((TempValue / 4) * 3));
				TempSpawn -= 3;
			}
			else if (--TempValue > 100)
			{
				OnGemSpawn.Broadcast(2);
				OnGemSpawn.Broadcast(1);
				TempValue = FMath::Max(0, ((TempValue / 3) * 2));
				TempSpawn -= 2;
			}
			else
			{
				--TempValue;
				OnGemSpawn.Broadcast(2);
				TempValue = FMath::Max(0, ((TempValue / 3) * 2));
				TempSpawn -= 1;
			}
		}
		else if (RandomNumber > 30)
		{
			if (--TempValue > 100)
			{
				OnGemSpawn.Broadcast(1);
				OnGemSpawn.Broadcast(1);
				TempValue = FMath::Max(0, ((TempValue / 4) * 3));
				TempSpawn -= 3;
			}
			else if (--TempValue > 50)
			{
				OnGemSpawn.Broadcast(1);
				TempValue = FMath::Max(0, ((TempValue / 3) * 2));
				TempSpawn -= 2;
			}
			else
			{
				--TempValue;
				OnGemSpawn.Broadcast(1);
				TempValue = FMath::Max(0, ((TempValue / 3) * 2));
				TempSpawn -= 1;
			}
		}
		else
		{
			--TempSpawn;
		}
	}
	bComplete = true;
}

bool AEnemyShipBase::InLineOfSight(FVector Target, bool bCheckSightDistance)
{
	FHitResult OutHit;

	FVector Start = GetActorLocation();
	FVector End = Target;
	bool bTargetFound = false;


	FCollisionQueryParams CollisionParams;

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

	bool bDraw = bIsDebug && bDrawLineOfSight;


	float LineThickness = 6.0f;
	uint8 Depth = 0;
	float LifeTime = 0.0f;
	


	AActor* HitActor = OutHit.GetActor();
	bool bIsHitPlayer = false;
	if (HitActor == GetWorld()->GetFirstPlayerController()->GetPawn())
		bIsHitPlayer = true;
	


	if (bCheckSightDistance && OutHit.Distance > LineOfSightDistance)
	{
		return  false;
	}

	//AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (bIsHitPlayer)
	{
		if (bDraw)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, LifeTime, Depth, LineThickness);
		}
		
		return true;

	}
	else
	{
		if (bDraw)
		{
			End = OutHit.Location;
			FVector Start2 = End;
			FVector End2 = TargetLocation;
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, LifeTime, Depth, LineThickness);
			DrawDebugLine(GetWorld(), Start2, End2, FColor::Orange, false, LifeTime, Depth, LineThickness);
		}
		 return false;
	}

}

