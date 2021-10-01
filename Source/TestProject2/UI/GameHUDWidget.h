// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "../PlayerShipBase.h"
#include "PlayerShipShieldBase.h"

#include "GameHUDWidget.generated.h"

/**
 * 
 */

 // Event for when the shields change
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FBindableEvent_ShieldsUp,
bool, bShieldsOnline);

UCLASS()
class TESTPROJECT2_API UGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	/*
	* Event for when shields change states, choose which shield
	* bar to show.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Shield Bar Selection")
		FBindableEvent_ShieldsUp OnShieldsUp;

	// Values 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float HealthPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float ShieldCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float ShieldMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float ShieldPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float ShieldBootPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float ShieldCoverOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		bool bReferenceShields = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		bool bShieldsDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		FText MoneyLabelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int Money = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
		TWeakObjectPtr<APlayerShipBase> OwnerShip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
		TWeakObjectPtr<APlayerShipShieldBase> OwnerShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
		TWeakObjectPtr<AActor> Owner;



	// Items
	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta=(BindWidget))
		UCanvasPanel* Root = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UProgressBar* HealthBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UProgressBar* ShieldBar = nullptr;

	//UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		//meta = (BindWidget))
		//UCanvasPanel* ShieldCoverCanvas = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UProgressBar* ShieldBootBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UImage* ShieldCoverImage = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UTextBlock* MoneyLabel = nullptr;



	// Functions and jazz
	UGameHUDWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void InitShields(float InShieldCurrent, float InShieldMax);

	UFUNCTION(BlueprintCallable)
		void UpdateHealthBar(float Value);

	UFUNCTION(BlueprintCallable)
		void UpdateShieldBar(float Delta);

	UFUNCTION(BlueprintCallable)
		void SetShieldCover(bool bActive);

	UFUNCTION(BlueprintCallable)
		void UpdateMoney(int InMoney);

	UFUNCTION(BlueprintImplementableEvent)
		void OnMoneyChanged();

};
