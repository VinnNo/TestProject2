// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerShipShieldBase.generated.h"

UCLASS()
class TESTPROJECT2_API APlayerShipShieldBase : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = MeshInner, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShieldInner;

	UPROPERTY(Category = MeshOuter, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShieldOuter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		float ShieldTimeMax = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		float ShieldTimeCurrent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		float ShieldDrain = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		float SizeMax = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		float StoredSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		float ScaleSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		int ScaleDirection = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		float MagnetPower = 1.0f;

	bool bShieldActive = false;
	
public:	
	// Sets default values for this actor's properties
	APlayerShipShieldBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void StartupShield(float CurrentTime, float Drain);

	UFUNCTION(BlueprintImplementableEvent)
		void TurnOffShield();

	void ShutDownShield();

	void UpdateShieldTime(float Delta);

	void ChangeSize(float Delta);

	UFUNCTION(BlueprintImplementableEvent)
		void OnLowHealth();

	UFUNCTION(BlueprintImplementableEvent)
		void OnHalfHealth();

};
