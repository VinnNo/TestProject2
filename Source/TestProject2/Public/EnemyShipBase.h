// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Character.h"
#include "EnemyShipBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FBindableEvent_SpawnGems,
int, SpawnSize);

UCLASS()
class TESTPROJECT2_API AEnemyShipBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyShipBase();

	UPROPERTY(BlueprintAssignable, Category = Loot)
		FBindableEvent_SpawnGems OnGemSpawn;

	// Hacks! Hold the Ship's mesh, letting character figure out movement
	UPROPERTY(Category = Ship, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* ShipSpringArm;

	// The Actual Ship
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;

	UPROPERTY(Category = Sight, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Sight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		AActor* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		float RememberTargetTime = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		float AcceptanceFound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		float AcceptanceLost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		float Acceptance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		float LineOfSightDistance = 4000.0f;

	UPROPERTY(Category = AIStuff, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bFoundPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		float PatrolTimerMax = RememberTargetTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		float PatrolTimerCurrent = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
	bool bPatrolTimerActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
	float IdleTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		FVector PatrolRandomLocation = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIStuff)
		bool bInSight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool bIsDebug = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool bDrawLineOfSight = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int LootValue = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int LootSpawnCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bShouldRotate = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float DistanceToPlayer;





	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		//enum ECollisionChannel LineOfSightChannel;


	int IDLE = 0;
	int PATROL = 1;
	int CHASE = 2;
	int STANDGROUND = 3;
	int FLEE = 4;

	UPROPERTY(Category = States, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int STATE = -1;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION(BlueprintCallable)
	int SetState(int Value);

	UFUNCTION(BlueprintImplementableEvent)
		void OnStateChanged();

	UFUNCTION(BlueprintImplementableEvent)
		void FoundPlayer();

	void RunStates(int Value);

	void RotateTowardsPlayer();

	FVector GetPlayerLocation();

	FRotator GetTargetRotation(FVector Target);

	void DoTimers(float Delta);
	
	UFUNCTION(BlueprintCallable)
	void StartPatrolTimer(bool bReset = false);

	UFUNCTION(BlueprintCallable)
		void SpawnLoot(bool &bComplete);

	UFUNCTION(BlueprintImplementableEvent)
		void PatrolTimerUp();

	UFUNCTION(BlueprintCallable)
		void CancelMovement();

	UFUNCTION(BlueprintCallable)
		bool InLineOfSight(FVector Target, bool bCheckSightDistance = false);
};
