// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "GameModeShip.h"

#include "WidgetWaveDisplay.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UWidgetWaveDisplay : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int WaveCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int WaveNext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int EnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int WaveTimeSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int WaveTimeMinutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		bool bFinalCountDown = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		bool bWaveActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	bool bUsePlaceholderTime = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
		TWeakObjectPtr<AGameModeShip> GameMode;


	// Items
	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UCanvasPanel* Root = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UTextBlock* WaveCountLabel = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UTextBlock* MinutesLabel = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UTextBlock* SecondsLabel = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Items",
		meta = (BindWidget))
		UTextBlock* EnemyCountLabel = nullptr;


	// Functions and Jazz
	UWidgetWaveDisplay(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void UpdateWidgetValues(int InWaveCurrent, int InTimeMinutes, int InTimeSeconds, int InEnemyCount, bool bInWaveActive);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSecondsPlaceHolder();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFinalCountDown();


};
