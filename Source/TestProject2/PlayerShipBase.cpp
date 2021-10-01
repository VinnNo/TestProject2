// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipBase.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "StaticsLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"

#include "EnemyShipBase.h"
#include "UI/WidgetWaveDisplay.h"

//const FName APlayerShipBase::TurnBinding("Turn");
//const FName APlayerShipBase::ThrusterBinding("Thruster");

// Sets default values
APlayerShipBase::APlayerShipBase()
{
	// The Mesh and Root
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMeshComponent"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Spacey/Meshes/Ships/PlayerShip/SM_PlayerShip.SM_PlayerShip"));

	if (ShipMesh.Succeeded())
	{
		ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	}

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->ArrowSize = 2.0f;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 3000.0f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -175.0f));

	// MiniMap Spring Arm
	MiniMapBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMapBoom"));
	MiniMapBoom->SetupAttachment(RootComponent);
	MiniMapBoom->SetUsingAbsoluteRotation(true);
	MiniMapBoom->TargetArmLength = 2000.0f;
	MiniMapBoom->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	MiniMapBoom->bDoCollisionTest = false;

	// MiniMap Capture
	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RT(TEXT("/Game/Spacey/Textures/MiniMaps/RT_MiniMap.RT_MiniMap"));

	MiniMapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMapCapture"));
	MiniMapCapture->SetupAttachment(MiniMapBoom, USpringArmComponent::SocketName);
	MiniMapCapture->ProjectionType = ECameraProjectionMode::Orthographic;
	MiniMapCapture->OrthoWidth = 3000.0f;
	// Default Settings
	MiniMapCapture->ShowFlags.Bloom = false;
	MiniMapCapture->ShowFlags.EyeAdaptation = false;
	MiniMapCapture->ShowFlags.MotionBlur = false;
	MiniMapCapture->ShowFlags.ToneCurve = false;
	MiniMapCapture->ShowFlags.SkyLighting = false;
	MiniMapCapture->ShowFlags.AmbientOcclusion = false;
	MiniMapCapture->ShowFlags.DynamicShadows = false;
	MiniMapCapture->ShowFlags.AmbientCubemap = false;
	MiniMapCapture->ShowFlags.LightFunctions = false;
	MiniMapCapture->ShowFlags.LightShafts = false;
	MiniMapCapture->ShowFlags.ReflectionEnvironment = false;
	MiniMapCapture->ShowFlags.TexturedLightProfiles = false;
	MiniMapCapture->ShowFlags.VolumetricFog = false;
	MiniMapCapture->ShowFlags.Lighting = false;
	MiniMapCapture->ShowFlags.PostProcessing = false;
	MiniMapCapture->ShowFlags.Particles = false;
	MiniMapCapture->ShowFlags.DeferredLighting = false;
	MiniMapCapture->ShowFlags.InstancedFoliage = false;
	MiniMapCapture->ShowFlags.InstancedGrass = false;
	MiniMapCapture->ShowFlags.Fog = false;
	//MiniMapCapture->ShowFlags.Atmosphere = false;
	MiniMapCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	MiniMapCapture->TextureTarget = RT.Object;

	// MiniMap Icon
	//Icon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Icon"));

	Sight = CreateDefaultSubobject<USphereComponent>(TEXT("Sight"));
	Sight->SetupAttachment(RootComponent);
	Sight->SetUsingAbsoluteRotation(true);
	Sight->SetSphereRadius(5000.0f);

	// Engine Particles
	PS_Engine_Left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Engine_Left"));
	//PS_Engine_Left->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("EngineLeft"));
	PS_Engine_Left->SetupAttachment(RootComponent, TEXT("EngineLeft"));

	PS_Engine_Right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Engine_Right"));
	//PS_Engine_Right->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("EngineRight"));
	PS_Engine_Right->SetupAttachment(RootComponent, TEXT("EngineRight"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PSystem(TEXT("/Game/Spacey/Particles/P_Trails.P_Trails"));

	if (PSystem.Succeeded())
	{
		PS_Engine_Left->SetTemplate(PSystem.Object);
		PS_Engine_Right->SetTemplate(PSystem.Object);
	}

	// Create Movement
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->MaxSpeed = 1000.0f;
	FloatingMovement->Acceleration = 500.0f;
	FloatingMovement->Deceleration = 100.0f;
	FloatingMovement->bConstrainToPlane = true;
	FloatingMovement->bSnapToPlaneAtStart = true;
	FloatingMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);


	// Creation Rotation
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);

	DirectionIndicator = CreateDefaultSubobject<USceneComponent>(TEXT("DirectionIndicator"));
	DirectionIndicator->SetupAttachment(RootComponent);
	DirectionIndicator->SetUsingAbsoluteRotation(true);

	Crosshair = CreateDefaultSubobject<USceneComponent>(TEXT("Crosshair"));
	Crosshair->SetupAttachment(DirectionIndicator);
	Crosshair->SetRelativeLocation(FVector(1540.0f, 0.0f, 0.0f));




	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called to bind functionality to input
void APlayerShipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	//PlayerInputComponent->BindAxis(ThrusterBinding);

	PlayerInputComponent->BindAxis("Thruster", this, &APlayerShipBase::ThrusterInput);

	// For classic Asteroids style turning
	//PlayerInputComponent->BindAxis("Turn", this, &APlayerShipBase::UpdateTurnInput);

	// For more modern style
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerShipBase::SetMoveRight);

	if (bIsMobile)
	{
		PlayerInputComponent->BindAxis("MoveForwardAlt", this, &APlayerShipBase::SetMoveUp);
	}
	else
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShipBase::SetMoveUp);
	}


}

// Called when the game starts or when spawned
void APlayerShipBase::BeginPlay()
{
	Super::BeginPlay();
	CameraNormal = CameraBoom->TargetArmLength;
	CrosshairRelativeLocation = Crosshair->GetRelativeLocation();

#if PLATFORM_ANDROID
	bIsMobile = true;
#endif
}

void APlayerShipBase::SetMoveRight(float Value)
{
	ControlDirection.Y = Value;
	DoTurn();
}

void APlayerShipBase::SetMoveUp(float Value)
{
	ControlDirection.X = Value;
	DoTurn();
}

void APlayerShipBase::DoTurn()
{
	if (bUseAsteroidsControls)
	{
		//DoTurnClassic(ControlDirection.X);
		UpdateTurnInput(ControlDirection.Y);
		return;
	}

	// Flip Y inputs
	/*
	if (bIsMobile && ControlDirection.X != 0.0f)
	{
		if (ControlDirection.X > 0.0f)
		{
			ControlDirection.X = -1.0f;
		}
		else if (ControlDirection.X < 0.0f)
		{
			ControlDirection.X = 1.0f;
		}
	}
	*/

	float Value = 0.0f;
	if ((ControlDirection.SizeSquared() > 0.0f))
	{
		// Base Comparables
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = GetActorLocation() + ControlDirection;

		// Target rotation - I only care about the Yaw. 
		FRotator TR = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);
		TR.Roll = 0.0f;
		TR.Pitch = 0.0f;
		

		//TargetControlRotation = TR;
		//TargetControlDirection = TargetLocation;

		// Current Rotation - Again, only care about Yaw.
		FRotator CR = GetActorRotation();
		CR.Pitch = 0.0f;
		CR.Roll = 0.0f;

		// I can be dumb, so let's deal with 0-360 tonight.
		float TD = TR.Clamp().Yaw;
		float CD = CR.Clamp().Yaw;

		// 5 degrees seems fair..
		bool bCanTurn = true;

		if ((TD > CD + AimRange) && (TD < CD - AimRange))
		{
			bCanTurn = false;
		}

		// Build the value to pass on.
		if (bCanTurn)
		{
			if ((TD > CD + AimRange))
			{
				if (TD > 270.0f && CD < 90.0f)
				{
					Value = -1.0f;
				}
				else
				{
					Value = 1.0f;
				}
			}
			else if (TD < CD - AimRange)
			{
				if (CD > 270.0f && TD < 90.0f)
				{
					Value = 1.0f;
				}
				else
				{
					Value = -1.0f;
				}
			}
		}
	}

	// Then pass that value
	if (Value != 0.0f)
	{
		DoTurnClassic(Value);
	}
	else
	{
		StopTurn();
	}

}

void APlayerShipBase::UpdateTurnInput(float Value)
{
	if (!bUseAsteroidsControls)
		return;

	if (Value != 0.0f)
	{
		DoTurnClassic(Value);
	}

	if (Value == 0.0f)// if (GetRM()->RotationRate != FRotator())
	{
		StopTurn();
	}
}


void APlayerShipBase::ThrusterInput(float Value)
{
	if (bIsMobile)
	{
		return;
	}

	if (ThrustersActiveValue != Value)
	{
		ThrustersActiveValue = Value;
		//UpdateThrusterInput(ThrustersActiveValue);
	}
}

void APlayerShipBase::UpdateThrusterInput(float Value)
{
	if (KnockBackVelocity != FVector(0.0f, 0.0f, 0.0f))
	{
		float Time = GetWorld()->DeltaTimeSeconds;
		KnockBackVelocity.Z = 0.0f;
		//GetFPM()->Velocity = KnockBackVelocity;
		KnockBackVelocity.X = UStaticsLibrary::Approach(KnockBackVelocity.X, 0.0f, (500.0f * Time));
		KnockBackVelocity.Y = UStaticsLibrary::Approach(KnockBackVelocity.Y, 0.0f, (500.0f * Time));
		AddMovementInput(KnockBackVelocity, 1.0f);
	}
	if (Value > 0.0f)
	{
		if (bEnginesOff)
		{
			ThrusterBurst();
			bEnginesOff = false;
		}
		FVector NewForward = Arrow->GetForwardVector();
		NewForward.Z = 0.0f;
		AddMovementInput(NewForward, Value);
		ThrustersSet(true);
	}
	else
	{
		ThrustersSet(false);
		if (bEnginesOff)
			bEnginesOff = false;
	}
}

void APlayerShipBase::UpdateThrustersAlt(float Value)
{
	if (!bIsMobile)
	{
		return;
	}
	if (ThrustersActiveValue != Value)
	{
		ThrustersActiveValue = Value;
		//UpdateThrusterInput(ThrustersActiveValue);
	}
}

void APlayerShipBase::DoTurnClassic(float Value)
{
	float Time = GetWorld()->DeltaTimeSeconds;

	CurrentTurnRate = GetRM()->RotationRate.Yaw;
	CurrentRollRate = GetActorRotation().Roll;

	if (Value > 0.0f)
	{
		if (CurrentTurnRate <= MaxTurn)
			CurrentTurnRate = UStaticsLibrary::Approach(CurrentTurnRate, MaxTurn, TurnRate * Time);

		if (CurrentRollRate <= MaxRoll)
			CurrentRollRate = UStaticsLibrary::Approach(CurrentRollRate, MaxRoll, RollRate * Time);
	}
	
	if (Value < 0.0f)
	{
		if (CurrentTurnRate >= -MaxTurn)
			CurrentTurnRate = UStaticsLibrary::Approach(CurrentTurnRate, -MaxTurn, TurnRate * Time);

		if (CurrentRollRate >= -MaxRoll)
			CurrentRollRate = UStaticsLibrary::Approach(CurrentRollRate, -MaxRoll, RollRate * Time);
	}

	GetRM()->RotationRate.Yaw = CurrentTurnRate;
	FRotator Rot = GetActorRotation();
	Rot.Pitch = 0.0f;
	Rot.Roll = CurrentRollRate;
	SetActorRotation(Rot);

	Rot.Roll = 0.0f;
	DirectionIndicator->SetRelativeRotation(Rot);

}

void APlayerShipBase::StopTurn()
{
	float Time = GetWorld()->DeltaTimeSeconds;

	CurrentTurnRate = GetRM()->RotationRate.Yaw;
	CurrentTurnRate = UStaticsLibrary::Approach(CurrentRollRate, 0.0f, (TurnRate / 2 /* (3 / 2)*/) * Time);
	GetRM()->RotationRate.Yaw = CurrentTurnRate;

	CurrentRollRate = GetActorRotation().Roll;
	CurrentRollRate = UStaticsLibrary::Approach(CurrentRollRate, 0.0f, RollRate * Time);


	FRotator Rot = GetActorRotation();
	Rot.Roll = CurrentRollRate;
	Rot.Pitch = 0.0f;
	SetActorRotation(Rot);

	Rot.Roll = 0.0f;
	DirectionIndicator->SetRelativeRotation(Rot);
}

// Called every frame
void APlayerShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateShipTimers(DeltaTime);
	UpdateCameraZoom(DeltaTime);
	UpdateBattleMode(DeltaTime);
	TraceForEnemies();
	UpdateThrusterInput(ThrustersActiveValue);
}

void APlayerShipBase::UpdateShipTimers(float Delta)
{
	UpdateShieldTime(Delta);
	UpdateShieldDownTime(Delta);
}

void APlayerShipBase::UpdateShieldTime(float Delta)
{
	if (bShieldTimeActive)
	{
		ShieldTimeCurrent += ShipShieldRegenRate * Delta;
		if (ShieldTimeCurrent > ShieldTimeMax)
		{
			bShieldTimeActive = false;
			ShieldTimeCurrent = ShieldTimeMax;
		}
	}
}

void APlayerShipBase::SetShieldStartupDelay()
{
	ShieldDownTime = 0.0f;
	bShieldsDown = true;
}

void APlayerShipBase::UpdateShieldDownTime(float Delta)
{
	if (bShieldsDown)
	{
		ShieldDownTime += (ShieldDownTimeRate * Delta);
		if (ShieldDownTime > 1.0f)
		{
			ShieldDownTime = 1.0f;
			bShieldsDown = false;
			bShieldTimeActive = true;
			ShieldTimeCurrent = 0.01f;
			OnShieldsUp();
		}
	}
}

void APlayerShipBase::SetBattleMode(bool bSetBattle)
{
	if (bSetBattle != bIsBattleMode)
	{
		bIsBattleMode = bSetBattle;
		bUpdateCamera = true;
		bCheckEnemies = true;
		OnBattleMode();
	}

}

void APlayerShipBase::UpdateBattleMode(float Delta)
{
	if (bCheckEnemies)
	{
		TArray<AActor*> Overlaps;
		Sight->GetOverlappingActors(Overlaps);
		EnemiesInRange = Overlaps.Num();
		if (Overlaps.Num() > 0)
		{
			SetBattleMode(true);
		}
		else
		{
			SetBattleMode(false);
			bCheckEnemies = false;
		}
	}
}

void APlayerShipBase::UpdateCameraZoom(float Delta)
{
	if (bUpdateCamera)
	{
		float BoomLength = CameraBoom->TargetArmLength;
		float TargetLength;
		if (bIsBattleMode)
		{
			TargetLength = CameraBattle;
		}
		else
		{
			TargetLength = CameraNormal;
		}

		if (BoomLength != TargetLength)
		{
			BoomLength = UStaticsLibrary::Approach(BoomLength, TargetLength, (CameraZoomSpeed * Delta));
			CameraBoom->TargetArmLength = BoomLength;
		}
		else
		{
			bUpdateCamera = false;
		}
	}
}

void APlayerShipBase::TraceForEnemies()
{
	Crosshair->SetRelativeLocation(CrosshairRelativeLocation);
	Crosshair->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));


	FVector Start = GetActorLocation();
	FVector End = Crosshair->GetComponentLocation();

	FCollisionQueryParams CollisionParams(FName(TEXT("Test!")), true, this);

	CollisionParams.AddIgnoredActor(this);

	FHitResult OutHit(ForceInit);

	//bool bIsHit = ActorLineTraceSingle(OutHit, Start, End, CollisionChannel, CollisionParams);
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, CollisionChannel, CollisionParams);
	//bool bIsHit = GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, CollisionParams, CollisionParams2);

	bool bDraw = bIsDebug && bDrawLineOfSight;

	//bool bIsHit = false;

	float LineThickness = DrawLineThickness;
	uint8 Depth = DrawLineDepth;
	float LifeTime = DrawLineLifeTime;

	if (bIsHit)
	{
		if (OutHit.bBlockingHit)
		{
			if (bDraw)
			{
				DrawDebugLine(GetWorld(), Start, OutHit.Location, FColor::Red, false, LifeTime, Depth, LineThickness);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Hit Actor is: %s"), *OutHit.GetActor()->GetName()));
			}

			if (OutHit.GetActor()->ActorHasTag(TEXT("Enemy")))
			{
				FVector Location = (OutHit.GetActor()->GetActorLocation());// + (OutHit.Location));
				Location.Z += 100.0f;
				Crosshair->SetWorldLocation(Location);
				Crosshair->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
				if (!bCrosshairLockedOn)
				{
					bCrosshairLockedOn = true;
					CrosshairLockedOn();
				}
			}
			else
			{
				Crosshair->SetWorldLocation(OutHit.Location);
			}
		}
		else
		{
			if (bDraw)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, LifeTime, Depth, LineThickness);
			}
			if (bCrosshairLockedOn)
			{
				bCrosshairLockedOn = false;
				CrosshairLockedOn();
			}
		}
	}
	else
	{
		if (bDraw)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, LifeTime, Depth, LineThickness);
		}
		if (bCrosshairLockedOn)
		{
			bCrosshairLockedOn = false;
			CrosshairLockedOn();
		}
	}

}

