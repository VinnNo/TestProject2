// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShipShieldBase.h"
#include "Components/StaticMeshComponent.h"
#include "StaticsLibrary.h"

// Sets default values
APlayerShipShieldBase::APlayerShipShieldBase()
{
	ShieldInner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComponent"));
	RootComponent = ShieldInner;

	ShieldOuter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldOuterMeshComponent"));
	ShieldOuter->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerShipShieldBase::BeginPlay()
{
	Super::BeginPlay();
	StoredSize = GetActorScale().X;
}

// Called every frame
void APlayerShipShieldBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateShieldTime(DeltaTime);
	ChangeSize(DeltaTime);
}

void APlayerShipShieldBase::StartupShield(float CurrentTime, float MaxTime)
{
	ShieldTimeCurrent = CurrentTime;
	ShieldDrain = MaxTime;
	bShieldActive = true;
}

void APlayerShipShieldBase::ShutDownShield()
{
	Destroy();
}

void APlayerShipShieldBase::UpdateShieldTime(float Delta)
{
	if (bShieldActive)
	{
		ShieldTimeCurrent -= ShieldDrain * Delta;
		
		if (ShieldTimeCurrent < 0.25f)
		{
			OnLowHealth();
		}
		else if (ShieldTimeCurrent < 0.6f)
		{
			OnHalfHealth();
		}
		if (ShieldTimeCurrent < 0.0f)
		{
			ShieldTimeCurrent = 0.0f;
			bShieldActive = false;
			TurnOffShield();
		}
	}
}

void APlayerShipShieldBase::ChangeSize(float Delta)
{
	float NewSize = GetActorScale().X;
	if (ScaleDirection > 0)
	{
		if (NewSize < (StoredSize + SizeMax))
		{
			NewSize = UStaticsLibrary::Approach(NewSize, (StoredSize + SizeMax), (ScaleSpeed * Delta));
		}
		else
		{
			ScaleDirection = -1;
		}
	}
	else if (ScaleDirection < 0)
	{
		if (NewSize > StoredSize)
		{
			NewSize = UStaticsLibrary::Approach(NewSize, StoredSize, (ScaleSpeed * Delta));
		}
		else
		{
			ScaleDirection = 1;
		}
	}
	SetActorScale3D(FVector(NewSize, NewSize, NewSize));

	FRotator ORot = GetActorRotation();

	ORot.Roll = -GetActorRotation().Roll;
	ORot.Pitch = -GetActorRotation().Pitch;
	ORot.Yaw = -GetActorRotation().Yaw;

	ShieldOuter->SetRelativeRotation(ORot);
}

