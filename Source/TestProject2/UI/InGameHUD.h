// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();





	// Primary draw call for the HUD.
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
};
