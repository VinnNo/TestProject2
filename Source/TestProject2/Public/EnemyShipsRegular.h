// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "EnemyShipBase.h"
#include "EnemyShipsRegular.generated.h"



/**
 * 
 */
UCLASS()
class TESTPROJECT2_API AEnemyShipsRegular : public AEnemyShipBase
{
	GENERATED_BODY()
public:
		AEnemyShipsRegular();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RunStates(int Value);

	UFUNCTION(BlueprintCallable)
	int SetState(int Value);
};
