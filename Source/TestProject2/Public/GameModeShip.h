// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "EnemyShipBase.h"
#include "../PlayerShipBase.h"

#include "GameModeShip.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API AGameModeShip : public AGameModeBase
{
	GENERATED_BODY()
public:

	AGameModeShip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int WaveCurrent = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bWaveActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WaveUpTimeCurrent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float WaveUpTimeMax = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector SpawnRange = FVector(25000.0f, 25000.0f, 1100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor *Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		APlayerShipBase* PlayerShip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool bPlayerDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool bCanGoInside = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int Type1Count = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int Type2Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int Type3Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int Type4Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int Type5Count = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int MaxType1 = 7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int MaxType2 = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int MaxType3 = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Waves)
		int MaxType4 = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time)
		int TimeSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time)
		int TimeMinutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemies)
		int EnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemies)
	float StartingIdleTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemies)
	float IdleTimeIncrement = 1.0f;






	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ships)
		TSubclassOf<AEnemyShipBase> Type1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ships)
		TSubclassOf<AEnemyShipBase> Type2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ships)
		TSubclassOf<AEnemyShipBase> Type3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ships)
		TSubclassOf<AEnemyShipBase> Type4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ships)
		TSubclassOf<AEnemyShipBase> Type5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ships)
		TArray<AEnemyShipBase*> EnemyShips;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
		void StartWave();

	UFUNCTION(BlueprintCallable)
		void EndWave();

	UFUNCTION(BlueprintCallable)
		void UpdateWaveTime(float Delta);

	UFUNCTION(BlueprintCallable)
		void UpdateEnemyShipCount();

	UFUNCTION(BlueprintCallable)
	void SetPlayerDead();

	UFUNCTION(BlueprintCallable)
	bool SortShipsByDistance(float DistA, float DistB);

	UFUNCTION(BlueprintImplementableEvent)
		void OnWaveStarted();

	UFUNCTION(BlueprintImplementableEvent)
		void OnTimeUpdated();

	UFUNCTION(BlueprintImplementableEvent)
		void OnWaveEnded();

	UFUNCTION(BlueprintCallable)
	void SetWaveShips();

	UFUNCTION(BlueprintImplementableEvent)
	void DoBossWave();

	UFUNCTION(BlueprintImplementableEvent)
		void OnPlayerDeath();

};
