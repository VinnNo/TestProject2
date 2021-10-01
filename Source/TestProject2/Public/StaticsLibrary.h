// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UStaticsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Interpolation")
		static float Approach(float start, float end, float shift);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Randamization")
		static void RandomizeVector(FVector InVector, FVector& OutVector );

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
		void GetPlayer(bool& bPlayerValid, AActor*& OutActor);
	
};
