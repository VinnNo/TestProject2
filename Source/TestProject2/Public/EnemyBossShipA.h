// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "EnemyShipBase.h"
#include "EnemyBossShipA.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API AEnemyBossShipA : public AEnemyShipBase
{
	GENERATED_BODY()
public:
	AEnemyBossShipA();

	UPROPERTY(Category = Rotation, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class URotatingMovementComponent* RotatingMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float RotSpeed = 270.0f;
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float RotDir = 1;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int SetState(int Value);

	void RunStates(int Value);

	FORCEINLINE class URotatingMovementComponent* GetRM() const { return RotatingMovement; }
};
