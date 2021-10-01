// Oh, boy. Here we go!


#include "GameModeShip.h"

#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "Kismet/KismetMathLibrary.h"

AGameModeShip::AGameModeShip()
{
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateWaveTime(DeltaTime);

}

void AGameModeShip::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerShip = Cast<APlayerShipBase>(Player);
}

void AGameModeShip::StartWave()
{
	SetWaveShips();

	FVector Loc;
	Loc.Z = SpawnRange.Z;
	FRotator Rot;
	FActorSpawnParameters SpawnInfo;
	EnemyShips.Empty();
	//AActor* Enemy;

	// Type 1
	if (Type1Count > 0)
	{
		for (int i = 0; i < Type1Count; ++i)
		{
			Loc.X = FMath::RandRange(-SpawnRange.X, SpawnRange.X);
			Loc.Y = FMath::RandRange(-SpawnRange.Y, SpawnRange.Y);

			GetWorld()->SpawnActor(Type1, &Loc, &Rot, SpawnInfo);
		}
	}

	if (Type2Count > 0)
	{
		for (int i = 0; i < Type2Count; ++i)
		{
			Loc.X = FMath::RandRange(-SpawnRange.X, SpawnRange.X);
			Loc.Y = FMath::RandRange(-SpawnRange.Y, SpawnRange.Y);

			GetWorld()->SpawnActor(Type2, &Loc, &Rot, SpawnInfo);
		}
	}

	if (Type3Count > 0)
	{
		for (int i = 0; i < Type3Count; ++i)
		{
			Loc.X = FMath::RandRange(-SpawnRange.X, SpawnRange.X);
			Loc.Y = FMath::RandRange(-SpawnRange.Y, SpawnRange.Y);

			GetWorld()->SpawnActor(Type3, &Loc, &Rot, SpawnInfo);
		}
	}

	if (Type4Count > 0)
	{
		for (int i = 0; i < Type4Count; ++i)
		{
			Loc.X = FMath::RandRange(-SpawnRange.X, SpawnRange.X);
			Loc.Y = FMath::RandRange(-SpawnRange.Y, SpawnRange.Y);

			GetWorld()->SpawnActor(Type4, &Loc, &Rot, SpawnInfo);
		}
	}

	if (Type5Count > 0)
	{
		for (int i = 0; i < Type4Count; ++i)
		{
			Loc.X = FMath::RandRange(-SpawnRange.X, SpawnRange.X);
			Loc.Y = FMath::RandRange(-SpawnRange.Y, SpawnRange.Y);

			GetWorld()->SpawnActor(Type5, &Loc, &Rot, SpawnInfo);
		}
	}

	TArray<AActor*> TempShips;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyShipBase::StaticClass(), TempShips);
	EnemyCount = TempShips.Num();

	for (int i = 0; i < EnemyCount - 1; ++i)
	{
		if (IsValid(TempShips[i]))
		{
			EnemyShips.Add(Cast<AEnemyShipBase>(TempShips[i]));
		}
	}

	FVector PlayerLocation;

	if (IsValid(PlayerShip))
	{
		PlayerLocation = PlayerShip->GetActorLocation();
	}

	Algo::SortBy(EnemyShips, &AEnemyShipBase::DistanceToPlayer);

	//EnemyShips.Sort([](const AEnemyShipBase& DistanceToPlayer, const AEnemyShipBase& DistanceToPlayer) { return LHS > RHS; });

	//SortedShips.Sort([](const EnemyShips& LHS, const EnemyShips& RHS) {return LHS > RHS});

	for (int Itr = 0; Itr < EnemyCount - 1; ++Itr)
	{
		AEnemyShipBase* EnemyShip = nullptr;
		/*
		if (WaveCurrent < 3)
		{
			IdleTimeIncrement = 1.0f;
		}
		*/
		if (IsValid(EnemyShips[Itr]))
		{
			EnemyShip = EnemyShips[Itr];
		}
		if (IsValid(EnemyShip))
		{
			float IdleIncrementOffset = 0.01f;

			if (WaveCurrent >= 9)
			{
				IdleIncrementOffset = 0.025f;
			}

			EnemyShip->IdleTime = StartingIdleTime;
			StartingIdleTime += IdleTimeIncrement;
			//IdleTimeIncrement += (IdleIncrementOffset * (EnemyCount / 2));

		}
	}

	if (WaveCurrent == 20)
	{
		DoBossWave();
	}
	bWaveActive = true;
	OnWaveStarted();
}

bool AGameModeShip::SortShipsByDistance(float DistA, float DistB)
{
	return DistA < DistB;
}

void AGameModeShip::EndWave()
{
	//SetWaveShips();
	/*
	Type1Count += 1;

	if (FMath::RandRange(1.0f, 100.0f) > 70.0f)
	{
		Type1Count += 1;
	}

	if (WaveCurrent >= 3)
	{
		Type2Count += 1;
		if (FMath::RandRange(1.0f, 100.0f) > 70.0f)
		{
			Type2Count += 1;
		}

		while (Type1Count > (Type2Count * 3))
		{
			Type1Count -= 1;
		}

	}

	if (WaveCurrent >= 7)
	{
		Type3Count += 1;
		if (FMath::RandRange(1.0f, 100.0f) > 70.0f)
		{
			Type2Count += 1;
		}

		while (Type2Count > (Type3Count * 3))
		{
			Type2Count -= 1;
		}
	}

	if (WaveCurrent >= 10)
	{
		Type4Count += 1;
		if (FMath::RandRange(1.0f, 100.0f) > 70.0f)
		{
			Type4Count += 1;
		}

		while (Type4Count > (Type3Count * 3))
		{
			Type3Count -= 1;
		}
	}

	if (WaveCurrent >= 15)
	{
		Type5Count += 1;
		if (FMath::RandRange(1.0f, 100.0f) > 70.0f)
		{
			Type5Count += 1;
		}
		while (Type5Count > (Type4Count * 3))
		{
			Type4Count -= 1;
		}

	}

	if (Type1Count > MaxType1)
	{
		Type1Count = MaxType1;
	}
	if (Type2Count > MaxType2)
	{
		Type2Count = MaxType2;
	}
	if (Type3Count > MaxType3)
	{
		Type3Count = MaxType3;
	}
	if (Type4Count > MaxType4)
	{
		Type4Count = MaxType4;
	}
	*/

	IdleTimeIncrement = 1.0f;
	StartingIdleTime = 0.0f;
	bWaveActive = false;
	WaveUpTimeCurrent = 0.0f;
	SetActorTickEnabled(true);
	WaveCurrent += 1;
	OnWaveEnded();
}

void AGameModeShip::UpdateEnemyShipCount()
{
	TArray<AActor*> TempShips;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyShipBase::StaticClass(), TempShips);

	EnemyCount = TempShips.Num();
	if (EnemyCount == 0)
	{
		EndWave();
	}
}

void AGameModeShip::UpdateWaveTime(float Delta)
{
	if (!bWaveActive)
	{
		WaveUpTimeCurrent += 1 * Delta;

		int TS = round((int)(WaveUpTimeMax - WaveUpTimeCurrent));
		int TM = 0; //round(TS / 60.0f);
		while (TS >= 60)
		{
			TM += 1;
			TS -= 60;
		}

		if (TimeSeconds != TS || TimeMinutes != TM)
		{
			TimeSeconds = TS;
			TimeMinutes = TM;
			OnTimeUpdated();
		}

		//TimeSeconds = round(WaveUpTimeMax - WaveUpTimeCurrent);

		if (WaveUpTimeCurrent > WaveUpTimeMax)
		{
			WaveUpTimeCurrent = 0.0f;
			//WaveCurrent += 1;
			StartWave();
			SetActorTickEnabled(false);
		}
	}
}

void AGameModeShip::SetWaveShips()
{
	Type1Count = 0;
	Type2Count = 0;
	Type3Count = 0;
	Type4Count = 0;
	Type5Count = 0;

	switch (WaveCurrent)
	{
		case 1:
		{
			Type1Count = 3;
			break;
		}
		case 2:
		{
			Type1Count = 6;
			break;
		}
		case 3:
		{
			Type1Count = 4;
			Type2Count = 1;
			break;
		}
		case 4:
		{
			Type1Count = 6;
			Type2Count = 2;
			break;
		}
		case 5:
		{
			Type1Count = 5;
			Type2Count = 3;
			break;
		}
		case 6:
		{
			Type1Count = 4;
			Type2Count = 2;
			Type3Count = 1;
			break;
		}
		case 7:
		{
			Type1Count = 5;
			Type2Count = 3;
			Type3Count = 2;
			break;
		}
		case 8:
		{
			Type1Count = 6;
			Type2Count = 4;
			Type3Count = 3;
			break;
		}
		case 9:
		{
			Type1Count = 20;
			break;
		}
		case 10:
		{
			Type1Count = 30;
			break;
		}
		case 11:
		{
			Type1Count = 5;
			Type2Count = 3;
			Type3Count = 1;
			Type4Count = 1;
			break;
		}
		case 12:
		{
			Type1Count = 6;
			Type2Count = 5;
			Type3Count = 2;
			Type4Count = 3;
			break;
		}
		case 13:
		{
			Type1Count = 8;
			Type2Count = 5;
			Type3Count = 5;
			Type4Count = 4;
			break;
		}
		case 14:
		{
			Type1Count = 15;
			Type2Count = 10;
			Type3Count = 2;
			break;
		}
		case 15:
		{
			Type1Count = 8;
			Type2Count = 4;
			Type3Count = 3;
			Type4Count = 1;
			Type5Count = 1;
			break;
		}
		case 16:
		{
			Type1Count = 10;
			Type2Count = 5;
			Type3Count = 4;
			Type4Count = 3;
			Type5Count = 2;
			break;
		}
		case 17:
		{
			Type1Count = 20;
			Type2Count = 10;
			Type3Count = 5;
			break;
		}
		case 18:
		{
			Type3Count = 5;
			Type4Count = 3;
			Type5Count = 2;
			break;
		}
		case 19:
		{
			Type1Count = 10;
			Type3Count = 2;
			Type4Count = 5;
			Type5Count = 3;
			break;
		}
		case 20:
		{
			break;
		}
	}
}

void AGameModeShip::SetPlayerDead()
{
	if (!bPlayerDead)
	{
		bPlayerDead = true;
		OnPlayerDeath();
		TArray<AActor*> TempShips;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyShipBase::StaticClass(), TempShips);
		EnemyCount = TempShips.Num();

		for (int i = 0; i < EnemyCount - 1; ++i)
		{
			if (IsValid(TempShips[i]))
			{
				AEnemyShipBase* TempShip = Cast<AEnemyShipBase>(TempShips[i]);
				TempShip->SetState(4);
			}
		}
	}
}