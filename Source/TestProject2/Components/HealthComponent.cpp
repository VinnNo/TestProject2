// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	HealthChanged_Implementation(1.0f, 1.0f, 1.0f);
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::IncrementHealth(float Value)
{
	// Nothing to see here, folks!
	if (HealthCurrent == HealthMax)
		return;

	float From = HealthCurrent;

	if (Value > 0.0f)
	{
		HealthCurrent = FMath::Min(HealthCurrent + Value, HealthMax);
		HealthChanged_Implementation(From, HealthCurrent, Value);
	}
}

void UHealthComponent::DecrementHealth(float Value)
{
	if (HealthCurrent == 0.0f)
		return;

	float From = HealthCurrent;

	if (Value > 0.0f)
	{
		HealthCurrent = FMath::Max(HealthCurrent - Value, 0.0f);

		if (HealthCurrent == 0.0f)
		{
			OnHealthDepleted_Implementation();
		}

		HealthChanged_Implementation(From, HealthCurrent, Value);

	}
}

float UHealthComponent::GetHealthAsPercent()
{
	return HealthCurrent / HealthMax;
}

void UHealthComponent::HealthChanged_Implementation(float FromVal, float ToVal, float ByVal)
{
	//OnHealthChanged.Broadcast(FromVal, ToVal, ByVal);
	OnHealthChanged.Broadcast();
}


void UHealthComponent::OnHealthDepleted_Implementation()
{
	OnHealthDepleted.Broadcast();
}

