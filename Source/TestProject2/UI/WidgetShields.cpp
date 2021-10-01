// Oh, boy. Here we go!


#include "WidgetShields.h"

#include "Engine.h"

UWidgetShields::UWidgetShields(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetShields::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetShields::SetShieldBaseValues(float InMax, float InDrain, float InRegen, float InBootUp, int InMoney)
{
	ShieldsMax = InMax;
	ShieldsDrain = InDrain;
	ShieldsRegen = InRegen;
	ShieldsBootUp = InBootUp;
	Money = InMoney;
	SetShieldValues();
}

void UWidgetShields::SetShieldValues()
{
	ShieldMaxVal = ShieldsMax / ShieldMaxShields;
	ShieldDrainVal = 1 - ShieldsDrain;//ShieldsDrain / ShieldMaxDrain;
	ShieldRegenVal = ShieldsRegen / ShieldMaxRegen;
	ShieldBootVal = ShieldsBootUp / ShieldMaxBoot;
	SetUpgradeCosts();
}

void UWidgetShields::SetUpgradeCosts()
{
	ShieldMaxCost = GetUpgradeCost(ShieldMaxVal);
	ShieldDrainCost = round( (ShieldDrainVal * (CostMultiplier * 2)) + 1000.0f );//(GetUpgradeCost(ShieldDrainVal) * 2);
	ShieldRegenCost = GetUpgradeCost(ShieldRegenVal);
	ShieldBootCost = GetUpgradeCost(ShieldBootVal);
}

int UWidgetShields::GetUpgradeCost(float Value)
{
	if (Value == 1.0f)
	{
		return 0;
	}
	if (Value == 0.0f)
	{
		return round(CostMultiplier * 0.05f);
	}
	return round(Value * CostMultiplier);
}

bool UWidgetShields::GetCanAfford(float Value)
{
	float NewVal;

	if (Value == 0.0f)
	{
		NewVal = (CostMultiplier);
	}
	else
	{
		NewVal = Value * CostMultiplier;
	}

	if (Money >= NewVal)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UWidgetShields::ReturnWidgetValues(float& OutMax, float& OutDrain, float& OutRegen, float& OutBoot, int& OutMoney)
{
	OutMax = ShieldsMax;
	OutDrain = ShieldsDrain;
	OutRegen = ShieldsRegen;
	OutBoot = ShieldsBootUp;
	OutMoney = Money;
}

void UWidgetShields::MenuSetSelected(int UpgradeToSelect)
{
	if (SelectedUpgrade == UpgradeToSelect)
		return;
	OnShieldSelectionChanged.Broadcast(UpgradeToSelect, SelectedUpgrade);
	SelectedUpgrade = UpgradeToSelect;
}

void UWidgetShields::PurchaseUpgrade(int Value, bool &bCouldNotAfford)
{
	bCouldNotAfford = false;

	if (Value > 0)
	{
		bool bUpgraded = false;
		int Price;
		switch (Value)
		{
			case 1:
			{
				if (ShieldMaxVal >= 1.0f)
				{
					bStatMaxed = true;
					ShieldMaxVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(ShieldMaxVal))
				{
					Price = GetUpgradeCost(ShieldMaxVal);
					Money = FMath::Max(0, Money - Price);
					ShieldsMax += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
			case 2:
			{
				if (ShieldRegenVal >= 1.0f)
				{
					bStatMaxed = true;
					ShieldRegenVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(ShieldRegenVal))
				{
					Price = GetUpgradeCost(ShieldRegenVal);
					Money = FMath::Max(0, Money - Price);
					ShieldsRegen += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
			case 3:
			{
				if (ShieldDrainVal >= 1.0f)
				{
					bStatMaxed = true;
					ShieldDrainVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				//if (GetCanAfford(ShieldDrainVal))
				else if (Money >= ShieldDrainCost)
				{
					Price = ShieldDrainCost;//GetUpgradeCost(ShieldDrainVal);
					Money = FMath::Max(0, Money - Price);
					ShieldsDrain -= (PurchaseUpgradeAmount / 2);
					bUpgraded = true;
				}
				break;
			}
			case 4:
			{
				if (ShieldBootVal >= 1.0f)
				{
					bStatMaxed = true;
					ShieldBootVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(ShieldBootVal))
				{
					Price = GetUpgradeCost(ShieldBootVal);
					Money = FMath::Max(0, Money - Price);
					ShieldsBootUp += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
		}
		if (bUpgraded)
		{
			SetShieldValues();
			SetUpgradeCosts();
		}
		else
		{
			bCouldNotAfford = true;
		}
	}
}

