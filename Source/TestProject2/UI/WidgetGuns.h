// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "WidgetGuns.generated.h"

/**
 * 
 */

 // Event for when the gun selection changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
FBindableEvent_MenuGunSelection,
int, GunWasSelected);

UCLASS()
class TESTPROJECT2_API UWidgetGuns : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable, Category = "MenuSelection")
		FBindableEvent_MenuGunSelection OnGunSelectionChanged;

	// Values Passed from the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		int Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float Fire1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float Fire2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float Power1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UserStats)
		float Power2;

	/*
	*  For internal Widgets
	*/

	// Post-Calculaion values for progress bars; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float FireVal1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float FireVal2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float PowerVal1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float PowerVal2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		int FireCost1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		int FireCost2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		int PowerCost1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		int PowerCost2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float CostMultiplier = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		float PurchaseUpgradeAmount = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetValues)
		bool bStatMaxed = false;

	// Cycle through Item Selections
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetNavigation)
		int SelectedMenuItem = 0;

	// The selected gun, slotted to be upgraded. 1 = GunLeft; 2 = GunRight.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetNavigation)
		int SelectedGun = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetNavigation)
		int SelectedUpgrade = 1;




	UWidgetGuns(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetGunBaseValues(float F1, float F2, float P1, float P2, int M);

	UFUNCTION(BlueprintCallable)
		void PurchasePowerUpgrade(int Value, bool &bCouldNotAfford);

	UFUNCTION(BlueprintCallable)
		void PurchaseFireUpgrade(int Value, bool &bCouldNotAfford);

	UFUNCTION(BlueprintCallable)
		void ReturnWidgetValues(float &F1, float &F2, float &P1, float &P2, int &M);

	UFUNCTION(BlueprintCallable)
		void MenuSetSelectedGun(int GunToSelect);

	//UFUNCTION(BlueprintImplementableEvent, Category = MenuSelection)
		//void OnSelectedGunChanged(int &SelectedGunChangedTo);
	


	void SetGunValues();

	void SetUpgradeCosts();

	UFUNCTION(BlueprintPure)
	int GetUpgradeCost(float Value);
	
	bool GetCanAfford(float Value);
};
