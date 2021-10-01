// Oh, boy. Here we go!


#include "WidgetShipBars.h"

#include "Engine.h" 

UWidgetShipBars::UWidgetShipBars(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetShipBars::NativeConstruct()
{
	Super::NativeConstruct();

	Root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), FName("Root"));
	WidgetTree->RootWidget = Root;

	if (WidgetTree)
	{
		//UWidget* RootWidget = GetRootWidget();
		//UCanvasPanel* CanvasPanel = static_cast<UWidget>(RootWidget);
		//UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());

	}

	//InitWidget();
}

void UWidgetShipBars::InitShields(float ShieldCurrent, float ShieldMax)
{
	ShieldsCurrent = ShieldCurrent;
	ShieldsMax = ShieldMax;
	ShipShieldPercent = GetAsPercent(ShieldsCurrent, ShieldsMax);
	if (ShipShieldsBar)
	{
		if (ShipShieldsBar->Percent != ShipShieldPercent)
		{
			ShipShieldsBar->SetPercent(ShipShieldPercent);
		}
	}

}

float UWidgetShipBars::GetAsPercent(float A, float B)
{
	return A / B;
}

void UWidgetShipBars::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateBars(InDeltaTime);
}

void UWidgetShipBars::UpdateBars(float Delta)
{
	UpdateShieldsBar(Delta);
}

void UWidgetShipBars::UpdateHealthBar(float Delta, float Value)
{
	if (ShipHealthBar)
	{
		ShipHealthBar->SetPercent(Value);
	}
}

void UWidgetShipBars::UpdateShieldsBar(float Delta)
{
	if (OwnerShip.IsValid())
	{
		SetShieldCover(OwnerShip->bShieldsDown);
	}

	if (bShieldsDown)
	{
		if (OwnerShip.IsValid())
		{
			ShieldBootUpPercent = OwnerShip->ShieldDownTime;
		}

		if (ShipShieldBootUpBar)
		{
			if (ShieldBootUpPercent >= 1.0f)
			{
				SetShieldCover(false);
				return;
			}
			if (ShipShieldBootUpBar->Percent != ShieldBootUpPercent)
			{
				ShipShieldBootUpBar->SetPercent(ShieldBootUpPercent);
			}
		}
	}
	else
	{
		if (bReferenceShields)
		{
			if (OwnerShield.IsValid())
			{
				ShipShieldPercent = GetAsPercent(OwnerShield->ShieldTimeCurrent, ShieldsMax);
				if (ShipShieldsBar)
				{
					if (ShipShieldsBar->Percent != ShipShieldPercent)
					{
						ShipShieldsBar->SetPercent(ShipShieldPercent);
					}
				}
			}
		}
		else
		{
			if (OwnerShip.IsValid())
			{
				ShipShieldPercent = GetAsPercent(OwnerShip->ShieldTimeCurrent, ShieldsMax);
				if (ShipShieldsBar)
				{
					if (ShipShieldsBar->Percent != ShipShieldPercent)
					{
						ShipShieldsBar->SetPercent(ShipShieldPercent);
					}
				}
			}
		}
	}
}

void UWidgetShipBars::UpdateShieldBootUpBar(float Delta)
{
	if (bShieldsDown)
	{

	}
}

void UWidgetShipBars::SetShieldCover(bool bActive)
{
	if (bActive)
	{
		if (!bShieldsDown)
		{
			bShieldsDown = true;
			if (ShipShieldCover)
			{
				//ShipShieldCover->SetRenderOpacity(1.0f);
				OnShieldsOnline.Broadcast(false);
			}
		}
	}
	else
	{
		if (bShieldsDown)
		{
			bShieldsDown = false;
			if (ShipShieldCover)
			{
				//ShipShieldCover->SetRenderOpacity(0.0f);
				bReferenceShields = false;
				if (OwnerShip.IsValid())
				{
					InitShields(OwnerShip->ShieldTimeCurrent, OwnerShip->ShieldTimeMax);
				}
				OnShieldsOnline.Broadcast(true);
			}
		}
	}
}