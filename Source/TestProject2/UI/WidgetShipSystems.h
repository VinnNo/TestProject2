// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "WidgetShipSystems.generated.h"

 // Event for when the gun selection changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FBindableEvent_MenuTypeSelection,
int, MenuWasSelected);
UCLASS()
class TESTPROJECT2_API UWidgetShipSystems : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "MenuSelection")
		FBindableEvent_MenuTypeSelection OnMenuWasSelected;


	// Player values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		int Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ShipHealthCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ShipHealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ShipHealthUpgradeMax = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float MagnetPowerCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float MagnetPowerMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float MagnetRangeCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float MagnetRangeMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ThrustPowerCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float ThrustPowerMax;



	// Widget values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float ShipHealthVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float ShipHealthUpgradeVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float MagnetPowerVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float MagnetRangeVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float ThrustPowerVal;


	// Prices and Point-Of-Sale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Purchase)
		int ShipHealthUpgradeCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Purchase)
		int ShipHealthRepairCost = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Purchase)
		int MagnetPowerCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Purchase)
		int ThrusterCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Purchase)
		float PurchaseUpgradeAmount = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Purchase)
		float CostMultiplier = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Purchase)
		bool bStatMaxed = false;


	// Navigation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetNavigation)
		int SelectedMenu = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetNavigation)
		int SelectedUpgrade = 1;





	UWidgetShipSystems(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetBaseValues(float InHP, float InHPMax, float InMagnet, float InMagnetMax, float InThrust, float InThrustMax, int InMoney);

	UFUNCTION(BlueprintCallable)
		void SetValues();

	UFUNCTION(BlueprintCallable)
		void MenuSetSelected(int Value);

	UFUNCTION(BlueprintCallable)
		void SetUpgradeCosts();

	UFUNCTION(BlueprintCallable)
		void PurchaseUpgrade(int Value, bool &bCouldNotAfford);

	UFUNCTION(BlueprintPure)
		int GetUpgradeCost(float Value);

	bool GetCanAfford(float Value);

	UFUNCTION(BlueprintCallable)
		void ReturnWidgetValues(float& HPCurrent, float& HPMax, float& MagCurrent, float& MagMax, float& ThrustCurrent, float& ThrustMax, int& M);

};
