// Oh, boy. Here we go!


#include "WidgetShipSystems.h"

#include "Engine.h"

UWidgetShipSystems::UWidgetShipSystems(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetShipSystems::NativeConstruct()
{
	Super::NativeConstruct();

}

void UWidgetShipSystems::SetBaseValues(float InHP, float InHPMax, float InMagnet, float InMagnetMax, float InThrust, float InThrustMax, int InMoney)
{
	ShipHealthCurrent = InHP;
	ShipHealthMax = InHPMax;

	MagnetPowerCurrent = InMagnet;
	MagnetPowerMax = InMagnetMax;

	ThrustPowerCurrent = InThrust;
	ThrustPowerMax = InThrustMax;

	Money = InMoney;

	SetValues();
	SetUpgradeCosts();
}

void UWidgetShipSystems::SetValues()
{
	ShipHealthVal = (ShipHealthCurrent / ShipHealthMax);
	ShipHealthUpgradeVal = (ShipHealthMax / ShipHealthUpgradeMax);
	MagnetPowerVal = (MagnetPowerCurrent / MagnetPowerMax);
	ThrustPowerVal = (ThrustPowerCurrent / ThrustPowerMax);

}

void UWidgetShipSystems::SetUpgradeCosts()
{
	ShipHealthUpgradeCost = GetUpgradeCost(ShipHealthUpgradeVal);
	MagnetPowerCost = GetUpgradeCost(MagnetPowerVal);
	ThrusterCost = GetUpgradeCost(ThrustPowerVal);
}

int UWidgetShipSystems::GetUpgradeCost(float Value)
{
	return round(Value * CostMultiplier);
}

void UWidgetShipSystems::MenuSetSelected(int Value)
{
	if (SelectedUpgrade == Value)
		return;
	SelectedUpgrade = Value;
	OnMenuWasSelected.Broadcast(Value);
}

void UWidgetShipSystems::PurchaseUpgrade(int Value, bool &bCouldNotAfford)
{
	bCouldNotAfford = false;
	if (Value > 0)
	{
		bool bUpgraded = false;
		switch (Value)
		{
			int Price;
			// Repairs
			case 1:
			{
				if (ShipHealthVal >= 1.0f)
				{
					bStatMaxed = true;
					ShipHealthVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				else if (Money >= ShipHealthRepairCost)
				{
					Money = FMath::Max(0, Money - ShipHealthRepairCost);
					ShipHealthCurrent = FMath::Min(ShipHealthMax, ShipHealthCurrent + 1.0f);
					bUpgraded = true;
				}
				break;
			}
			// Upgrade Health
			case 2:
			{
				if (ShipHealthUpgradeVal >= 1.0f)
				{
					bStatMaxed = true;
					ShipHealthUpgradeVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(ShipHealthUpgradeVal))
				{
					Price = ShipHealthUpgradeCost;
					Money = FMath::Max(0, Money - Price);
					ShipHealthMax += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
			// Upgrade Magnet Power
			case 3:
			{
				if (MagnetPowerVal >= 1.0f)
				{
					bStatMaxed = true;
					MagnetPowerVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(MagnetPowerVal))
				{
					Price = MagnetPowerCost;
					Money = FMath::Max(0, Money - Price);
					MagnetPowerCurrent += PurchaseUpgradeAmount;
					bUpgraded = true;
				}
				break;
			}
			// Upgrade Thrusters
			case 4:
			{
				if (ThrustPowerVal >= 1.0f)
				{
					bStatMaxed = true;
					ThrustPowerVal = 1.0f;
					bCouldNotAfford = true;
					return;
				}
				else if (GetCanAfford(ThrustPowerVal))
				{
					Price = ThrusterCost;
					Money = FMath::Max(0, Money - Price);
					ThrustPowerCurrent += 50.0f;
					bUpgraded = true;
				}
				break;
			}
		}
		if (bUpgraded)
		{
			SetValues();
			SetUpgradeCosts();
		}
		else
		{
			bCouldNotAfford = true;
		}
	}
}

bool UWidgetShipSystems::GetCanAfford(float Value)
{
	if (Money >= GetUpgradeCost(Value))
	{
		return true;
	}
	return false;
}

void UWidgetShipSystems::ReturnWidgetValues(float& HPCurrent, float& HPMax, float& MagCurrent, float& MagMax, float& ThrustCurrent, float& ThrustMax, int& M)
{
	HPCurrent = ShipHealthCurrent;
	HPMax = ShipHealthMax;

	MagCurrent = MagnetPowerCurrent;
	MagMax = MagnetPowerMax;

	ThrustCurrent = ThrustPowerCurrent;
	ThrustMax = ThrustPowerMax;

	M = Money;
}

