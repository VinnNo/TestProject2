// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPROJECT2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/*
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float From, float To, float By);

	DECLARE_DELEGATE(FOnHealthDepleted);

	FOnHealthChanged HealthChanged;
	FOnHealthDepleted HealthDepleted;
	*/

	//DECLARE_EVENT(FHealthChanged, FHealthChangedEvent);

	//FHealthChangedEvent HCE;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepletedSignature);
	//DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangedSignature, float&, float From, float&, float To, float&, float By);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChangedSignature);

	// Sets default values for this component's properties
	UHealthComponent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float HealthMax = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float HealthCurrent = HealthMax;

	UPROPERTY(BlueprintAssignable, Category = "Custom")
		FOnHealthDepletedSignature OnHealthDepleted;

	UPROPERTY(BlueprintAssignable, Category = "Custom")
		FOnHealthChangedSignature OnHealthChanged;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void IncrementHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void DecrementHealth(float Value);

	UFUNCTION(BlueprintPure)
	float GetHealthAsPercent();

	UFUNCTION()
	void HealthChanged_Implementation(float FromVal, float ToVal, float ByVal);

	//UFUNCTION(BlueprintImplementableEvent)
		//void OnHealthChanged();

	UFUNCTION()
		void OnHealthDepleted_Implementation();


};
