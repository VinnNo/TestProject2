// Oh, boy. Here we go!


#include "WidgetWaveDisplay.h"

#include "Engine.h"

UWidgetWaveDisplay::UWidgetWaveDisplay(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetWaveDisplay::NativeConstruct()
{
	Super::NativeConstruct();

}

void UWidgetWaveDisplay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UWidgetWaveDisplay::UpdateWidgetValues(int InWaveCurrent, int InTimeMinutes, int InTimeSeconds, int InEnemyCount, bool bInWaveActive)
{
	if (WaveTimeSeconds <= 5 && WaveTimeSeconds != InTimeSeconds)
	{
		OnFinalCountDown();
	}

	WaveCurrent = InWaveCurrent;
	WaveTimeMinutes = InTimeMinutes;
	WaveTimeSeconds = InTimeSeconds;
	EnemyCount = InEnemyCount;
	bWaveActive = bInWaveActive;

	if (WaveTimeSeconds < 10 && !bUsePlaceholderTime)
	{
		bUsePlaceholderTime = true;
		OnSecondsPlaceHolder();
	}
	else if (WaveTimeSeconds >= 10 && bUsePlaceholderTime)
	{
		bUsePlaceholderTime = false;
		OnSecondsPlaceHolder();
	}

	if (EnemyCountLabel)
	{
		FString EnemyString = FString::FromInt(EnemyCount);
		EnemyCountLabel->SetText(FText::FromString(EnemyString));
	}

	if (WaveCountLabel)
	{
		FString WaveString = FString::FromInt(WaveCurrent);
		WaveCountLabel->SetText(FText::FromString(WaveString));
	}

	if (bWaveActive)
	{
		FText TimeText = FText::FromString(FString::FromInt(0));
		if (MinutesLabel && SecondsLabel)
		{
			MinutesLabel->SetText(TimeText);
			SecondsLabel->SetText(TimeText);
			if (!bUsePlaceholderTime)
			{
				bUsePlaceholderTime = true;
				OnSecondsPlaceHolder();
			}
		}
	}

	if (MinutesLabel)
	{
		FString MinutesString = FString::FromInt(WaveTimeMinutes);
		MinutesLabel->SetText(FText::FromString(MinutesString));
	}

	if (SecondsLabel)
	{
		FString SecondsString = FString::FromInt(WaveTimeSeconds);
		SecondsLabel->SetText(FText::FromString(SecondsString));
	}
}

