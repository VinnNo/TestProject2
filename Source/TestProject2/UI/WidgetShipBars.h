// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "../PlayerShipBase.h"
#include "PlayerShipShieldBase.h"

#include "WidgetShipBars.generated.h"

/**
 * 
 */

 // Event for when the gun selection changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FBindableEvent_ShieldsOnline,
bool, bShieldsOnline);
UCLASS(Abstract)
class TESTPROJECT2_API UWidgetShipBars : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWidgetShipBars(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "MenuSelection")
		FBindableEvent_ShieldsOnline OnShieldsOnline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* Root = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* ShipHealthBar = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* ShipShieldsBar = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* ShipShieldCover = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* ShipShieldBootUpBar = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* ShieldCoverImage = nullptr;


	// Values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShipHealthPercent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldsCurrent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldsMax = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShipShieldPercent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldBootUpPercent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float bShieldsDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldsDownRenderOpacity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bReferenceShields = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TWeakObjectPtr<APlayerShipBase> OwnerShip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TWeakObjectPtr<APlayerShipShieldBase> OwnerShield;


	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitShields(float ShieldCurrent, float ShieldMax);

	UFUNCTION(BlueprintCallable)
	float GetAsPercent(float A, float B);

	UFUNCTION(BlueprintCallable)
	void UpdateBars(float Delta);

	UFUNCTION(BlueprintCallable)
		void UpdateHealthBar(float Delta, float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateShieldsBar(float Delta);

	UFUNCTION(BlueprintCallable)
	void UpdateShieldBootUpBar(float Delta);

	UFUNCTION(BlueprintCallable)
	void SetShieldCover(bool bActive);
};
