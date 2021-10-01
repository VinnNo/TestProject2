// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Pawn.h"

#include "PlayerShipBase.generated.h"

UCLASS()
class TESTPROJECT2_API APlayerShipBase : public APawn
{
	GENERATED_BODY()

public:
	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(Category = Direction, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* Arrow;

	// Mini Map
	UPROPERTY(Category = MiniMap, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* MiniMapBoom;

	UPROPERTY(Category = MiniMap, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* MiniMapCapture;

	UPROPERTY(Category = MiniMap, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Sight;

	//UPROPERTY(Category = MiniMap, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		//class UPaperSpriteComponent* Icon;

	UPROPERTY(Category = Thrusters, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Engine_Right;

	UPROPERTY(Category = Thrusters, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Engine_Left;

	UPROPERTY(Category = Direction, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DirectionIndicator;

	UPROPERTY(Category = Direction, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* Crosshair;



	// Movements

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UFloatingPawnMovement* FloatingMovement;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class URotatingMovementComponent* RotatingMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float TurnRate = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxTurn = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float CurrentTurnRate = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float RollRate = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxRoll = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float CurrentRollRate = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float RollSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
		bool bEnginesOff = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldTimeMax = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldTimeCurrent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bShieldTimeActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShipShieldRegenRate = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldDrainRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldDownTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldDownTimeRate = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bShieldsDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector CrosshairRelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bCrosshairLockedOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MagnetPowerCurrent = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MagnetPowerMax = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ThrusterPowerCurrent = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ThrusterPowerMax = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector KnockBackVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ThrustersActiveValue = 0.0f; 



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraNormal = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraBattle = 6000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool bIsBattleMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool bUpdateCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraZoomSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool bCheckEnemies = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		int32 EnemiesInRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		bool bUseAsteroidsControls = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		float AimRange = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		FVector ControlDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		FVector TargetControlDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		FRotator TargetControlRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		float DebugDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		FRotator DebugCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		FRotator DebugTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		bool bIsMobile = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool bIsDebug = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool bDrawLineOfSight = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		float DrawLineThickness = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		float DrawLineLifeTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		uint8 DrawLineDepth = 0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		//TArray<TWeakObjectPtr<AActor>> IgnoredTraceActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		TEnumAsByte<ECollisionChannel> CollisionChannel;









	// Static names for axis bindings
	//static const FName TurnBinding;
	//static const FName ThrusterBinding;
	//static const FName FireForwardBinding;
	//static const FName FireRightBinding;

	// Sets default values for this pawn's properties
	APlayerShipBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateTurnInput(float Value);

	void ThrusterInput(float Value);

	void UpdateThrusterInput(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateThrustersAlt(float Value);

	void SetMoveRight(float Value);

	void SetMoveUp(float Value);

	void DoTurn();

	void DoTurnClassic(float Value);

	void StopTurn();

	void UpdateShieldTime(float Delta);

	void UpdateShieldDownTime(float Delta);

	void UpdateShipTimers(float Delta);

	UFUNCTION(BlueprintCallable)
		void SetShieldStartupDelay();

	UFUNCTION(BlueprintImplementableEvent)
		void OnShieldsUp();

	UFUNCTION(BlueprintImplementableEvent)
		void ThrustersSet(bool bSet = false);

	UFUNCTION(BlueprintImplementableEvent)
		void ThrusterBurst();

	UFUNCTION(BlueprintCallable)
		void SetBattleMode(bool bSetBattle);

	UFUNCTION(BlueprintImplementableEvent)
		void OnBattleMode();

	void UpdateBattleMode(float Delta);

	void UpdateCameraZoom(float Delta);

	UFUNCTION(BlueprintImplementableEvent)
		void CrosshairLockedOn();

	void TraceForEnemies();




	FORCEINLINE class UStaticMeshComponent* GetShip() const { return ShipMeshComponent; }
	FORCEINLINE class UFloatingPawnMovement* GetFPM() const { return FloatingMovement;  }
	FORCEINLINE class URotatingMovementComponent* GetRM() const { return RotatingMovement;  }


};
