// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGamePilotHUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API AInGamePilotHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGamePilotHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


	
};
