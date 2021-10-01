// Oh, boy. Here we go!


#include "WidgetGuns.h"

#include "Engine.h"

UWidgetGuns::UWidgetGuns(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetGuns::NativeConstruct()
{
	Super::NativeConstruct();

}

void UWidgetGuns::SetGunBaseValues(float F1, float F2, float P1, float P2, int M)
{
	Fire1 = F1;
	Fire2 = F2;
	Power1 = P1;
	Power2 = P2;
	Money = M;
	SetGunValues();
}

void UWidgetGuns::SetGunValues()
{
	FireVal1 = (Fire1 / 100);
	FireVal2 = (Fire2 / 100);

	PowerVal1 = (Power1 / 100);
	PowerVal2 = (Power2 / 100);
	SetUpgradeCosts();
}

void UWidgetGuns::SetUpgradeCosts()
{
	FireCost1 = GetUpgradeCost(FireVal1);
	FireCost2 = GetUpgradeCost(FireVal2);
	PowerCost1 = GetUpgradeCost(PowerVal1);
	PowerCost2 = GetUpgradeCost(PowerVal2);
}

int UWidgetGuns::GetUpgradeCost(float Value)
{
	if (Value == 1.0f)
	{
		return 0;
	}
	return round(Value * CostMultiplier);
}

bool UWidgetGuns::GetCanAfford(float Value)
{
	float NewVal = Value * CostMultiplier;
	if (Money >= NewVal)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UWidgetGuns::ReturnWidgetValues(float &F1, float &F2, float &P1, float &P2, int &M)
{
	F1 = Fire1;
	F2 = Fire2;
	P1 = Power1;
	P2 = Power2;
	M = Money;
}

void UWidgetGuns::PurchaseFireUpgrade(int Value, bool &bCouldNotAfford)
{
	/*
	* 1 = Fire1
	* 2 = Fire2
	*/
	bCouldNotAfford = false;
	if (Value > 0)
	{
		bool bUpgraded = false;

		switch (Value)
		{
			case 1:
			{
				if (FireVal1 >= 1.0f)
				{
					FireVal1 = 1.0f;
					bStatMaxed = true;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(FireVal1))
				{
					int Price = GetUpgradeCost(FireVal1);
					Money = FMath::Max(0, Money - Price);
					Fire1 += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
			case 2:
			{
				if (FireVal2 >= 1.0f)
				{
					FireVal2 = 1.0f;
					bStatMaxed = false;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(FireVal2))
				{
					int Price = GetUpgradeCost(FireVal2);
					Money = FMath::Max(0, Money - Price);
					Fire2 += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
		}
		if (bUpgraded)
		{
			SetGunValues();
			SetUpgradeCosts();
		}
		else
		{
			bCouldNotAfford = true;
		}
	}
}

void UWidgetGuns::PurchasePowerUpgrade(int Value, bool &bCouldNotAfford)
{
	/*
	* 0 = Must not have intended to purchase
	* 1 = Power1
	* 2 = Power2
	*/
	bCouldNotAfford = false;
	if (Value > 0)
	{
		bool bUpgraded = false;
		switch (Value)
		{
			case 1:
			{
				if (PowerVal1 >= 1.0f)
				{
					PowerVal1 = 1.0f;
					bStatMaxed = true;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(PowerVal1))
				{
					int Price = GetUpgradeCost(PowerVal1);
					Money = Money - FMath::Max(0, Price);
					Power1 += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
			case 2:
			{
				if (PowerVal2 >= 1.0f)
				{
					PowerVal2 = 1.0f;
					bStatMaxed = true;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(PowerVal2))
				{
					int Price = GetUpgradeCost(PowerVal2);
					Money = Money - FMath::Max(0, Price);
					Power2 += PurchaseUpgradeAmount;
					//bCouldNotAfford = true;
					bUpgraded = true;
				}
				break;
			}
		}
		if (bUpgraded)
		{
			SetGunValues();
			SetUpgradeCosts();
		}
		else
		{
			bCouldNotAfford = true;
		}
	}
}

void UWidgetGuns::MenuSetSelectedGun(int GunToSelect)
{
	if (SelectedGun == GunToSelect)
		return;
	SelectedGun = GunToSelect;
	//OnSelectedGunChanged(SelectedGun);
	OnGunSelectionChanged.Broadcast(SelectedGun);
}