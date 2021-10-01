// Oh, boy. Here we go!


#include "GameHUDWidget.h"

#include "Engine.h" 

UGameHUDWidget::UGameHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ShieldBootBar)
	{
		ShieldBootBar->SetRenderOpacity(0.0f);
	}
}

void UGameHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateShieldBar(InDeltaTime);
}

void UGameHUDWidget::InitShields(float InShieldCurrent, float InShieldMax)
{
	ShieldCurrent = InShieldCurrent;
	ShieldMax = InShieldMax;

	ShieldPercent = (InShieldCurrent / InShieldMax);
	if (ShieldBar)
	{
		ShieldBar->SetPercent(ShieldPercent);
	}
}

void UGameHUDWidget::UpdateHealthBar(float Value)
{
	HealthPercent = Value;
	if (HealthBar && (HealthBar->Percent != HealthPercent))
	{
		HealthBar->SetPercent(HealthPercent);
	}
}

void UGameHUDWidget::UpdateShieldBar(float Delta)
{
	if (OwnerShip.IsValid())
	{
		SetShieldCover(OwnerShip->bShieldsDown);
	}

	if (bShieldsDown)
	{
		if (OwnerShip.IsValid())
		{
			ShieldBootPercent = OwnerShip->ShieldDownTime;
		}

		if (ShieldBootBar)
		{
			if (ShieldBootPercent >= 1.0f)
			{
				SetShieldCover(false);
				return;
			}
			ShieldBootBar->SetPercent(ShieldBootPercent);
		}
	}
	else
	{
		if (bReferenceShields)
		{
			if (OwnerShield.IsValid())
			{
				ShieldPercent = (OwnerShield->ShieldTimeCurrent / OwnerShield->ShieldTimeMax);
				if (ShieldBar)
				{
					ShieldBar->SetPercent(ShieldPercent);
				}
			}
		}
		else
		{
			if (OwnerShip.IsValid())
			{
				ShieldPercent = (OwnerShip->ShieldTimeCurrent / OwnerShip->ShieldTimeMax);
				if (ShieldBar)
				{
					ShieldBar->SetPercent(ShieldPercent);
					//if (GEngine)
						//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
				}
			}
		}
	}
}

void UGameHUDWidget::SetShieldCover(bool bActive)
{
	if (bActive)
	{
		if (!bShieldsDown)
		{
			bShieldsDown = true;
			if (ShieldBootBar)
			{
				OnShieldsUp.Broadcast(false);
				ShieldBootBar->SetRenderOpacity(1.0f);
			}
		}
	}
	else
	{
		if (bShieldsDown)
		{
			bShieldsDown = false;
			if (ShieldBootBar)
			{
				bReferenceShields = false;
				if (OwnerShip.IsValid())
				{
					InitShields(OwnerShip->ShieldTimeCurrent, OwnerShip->ShieldTimeMax);
				}
				ShieldBootBar->SetRenderOpacity(0.0f);
				OnShieldsUp.Broadcast(true);
			}
		}
	}
}

void UGameHUDWidget::UpdateMoney(int InMoney)
{
	Money = InMoney;
	FString StrMoney = FString::FromInt(Money);
	MoneyLabelText = FText::FromString(StrMoney);
	MoneyLabel->SetText(MoneyLabelText);
	OnMoneyChanged();
}


