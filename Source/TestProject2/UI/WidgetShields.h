// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "WidgetShields.generated.h"

 // Event for when the gun selection changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
FBindableEvent_MenuShieldSelection,
int, ShieldWasSelected,
int, ShieldPrevSelected);

UCLASS()
class TESTPROJECT2_API UWidgetShields : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UWidgetShields(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "MenuSelection")
		FBindableEvent_MenuShieldSelection OnShieldSelectionChanged;

	// Base Values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ShieldsMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ShieldsDrain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ShieldsRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ShieldsBootUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		int Money;


	// Max upgrade values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldMaxShields = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldMaxDrain = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldMaxRegen = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldMaxBoot = 1.0f;

	// Percents
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldMaxVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldDrainVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldRegenVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float ShieldBootVal;

	// Costs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		int ShieldMaxCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		int ShieldDrainCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		int ShieldRegenCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		int ShieldBootCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float CostMultiplier = 15000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		float PurchaseUpgradeAmount = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetNavigation)
		int SelectedUpgrade = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetNavigation)
		int PreviousUpgrade = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetStats)
		bool bStatMaxed = false;



	UFUNCTION(BlueprintCallable)
		void SetShieldBaseValues(float InMax, float InDrain, float InRegen, float InBootUp, int InMoney);

	UFUNCTION(BlueprintCallable)
		void SetUpgradeCosts();

	void SetShieldValues();

	UFUNCTION(BlueprintCallable)
		void PurchaseUpgrade(int Value, bool& bCouldNotAfford);

	UFUNCTION(BlueprintCallable)
		int GetUpgradeCost(float Value);

	UFUNCTION(BlueprintCallable)
		bool GetCanAfford(float Value);

	UFUNCTION(BlueprintCallable)
		void MenuSetSelected(int UpgradeToSelect);

	UFUNCTION(BlueprintCallable)
		void ReturnWidgetValues(float& OutMax, float& OutDrain, float& OutRegen, float& OutBoot, int& OutMoney);
};
