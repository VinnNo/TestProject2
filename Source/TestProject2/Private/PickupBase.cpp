// Oh, boy. Here we go!


#include "PickupBase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "Engine/StaticMesh.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "UObject/ConstructorHelpers.h"

#include "DrawDebugHelpers.h"

#include "StaticsLibrary.h"

#include "../PlayerShipBase.h"
#include "PlayerShipShieldBase.h"


// Sets default values
APickupBase::APickupBase()
{
	GemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GemMesh"));
	RootComponent = GemMesh;

	Sight = CreateDefaultSubobject<USphereComponent>(TEXT("Sight"));
	Sight->SetupAttachment(RootComponent);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupBase::SetRotation()
{
	float RandomX = FMath::RandRange(-RandomRotationSpeed, RandomRotationSpeed);
	float RandomY = FMath::RandRange(-RandomRotationSpeed, RandomRotationSpeed);
	float RandomZ = FMath::RandRange(-RandomRotationSpeed, RandomRotationSpeed);

	RotatingMovement->RotationRate = FRotator(RandomX, RandomY, RandomZ);
}

void APickupBase::RandomizeAll()
{
	if (MeshList.Num() > 0)
	{
		TArray<UStaticMesh*> MeshArray = MeshList.Array();
		int32 RandomNumber = round( FMath::RandRange(0.0f, ((float)MeshList.Num() - 1)) );

		if (MeshArray[RandomNumber] != nullptr)
		{
			RandomMesh = MeshArray[RandomNumber];
		}
	}

	if (MaterialList.Num() > 0)
	{
		TArray<UMaterialInstance*> MaterialArray = MaterialList.Array();
		int32 RandomNumber = round( FMath::RandRange(0.0f, ((float)MaterialList.Num() - 1)) );

		if (MaterialArray[RandomNumber] != nullptr)
		{
			RandomMaterial = MaterialArray[RandomNumber];
		}
	}

	if (ValueRange != 0)
	{
		RandomValue = BaseValue + round(FMath::RandRange(-ValueRange, ValueRange));
	}

	if (ScaleRange != 0.0f)
	{
		float SomeNumber = FMath::RandRange(-ScaleRange, ScaleRange);
		RandomScale = FVector(SomeNumber, SomeNumber, SomeNumber);
	}
	OnRandomized();
}



// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToTarget(DeltaTime);
}

void APickupBase::MoveToTarget(float Delta)
{
	if (!WasRecentlyRendered())
	{
		return;
	}
	float Multiplier = 1.0f;
	float TempSpeedMax = SpeedMax;
	float Radius = Sight->GetUnscaledSphereRadius();

	TArray<AActor*> Shields;
	if (Shields.Num() == 0.0f)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerShipShieldBase::StaticClass(), Shields);
	}
	if (Shields.Num() != 0)
	{

		APlayerShipShieldBase* Shield = static_cast<APlayerShipShieldBase*>(Shields[0]);//Cast<APlayerShipShieldBase>(Shields[0]);
		if (Shield != nullptr)
		{
			Multiplier = Shield->MagnetPower;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Hit Actor is: %s"), *Shield->GetName()));
		}
		Sight->SetSphereRadius(Sight->GetUnscaledSphereRadius() * Multiplier);
		TempSpeedMax *= Multiplier;
	}

	if (bFoundPlayer && TargetActor != nullptr)
	{
		// Current vs target locations
		FVector CL = GetActorLocation();
		FVector TL = TargetActor->GetActorLocation();

		CL.X = UStaticsLibrary::Approach(CL.X, TL.X,((Speed * Delta) * Multiplier));
		CL.Y = UStaticsLibrary::Approach(CL.Y, TL.Y, ((Speed * Delta) * Multiplier));
		CL.Z = UStaticsLibrary::Approach(CL.Z, TL.Z, ((Speed * Delta) * Multiplier));

		SetActorLocation(CL);

		Speed = UStaticsLibrary::Approach(Speed, TempSpeedMax, ((Speed * Delta) * Multiplier));
	}

	if (Sight->GetUnscaledSphereRadius() != Radius)
	{
		Sight->SetSphereRadius(Radius);
	}

}

void APickupBase::SetPlayerFound(bool bFound)
{
	if (bFoundPlayer == bFound)
		return;
	bFoundPlayer = bFound;
	//SetActorTickEnabled(bFound);
	Speed = SpeedStart;
}

