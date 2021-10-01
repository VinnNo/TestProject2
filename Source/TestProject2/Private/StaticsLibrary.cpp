// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticsLibrary.h"

float UStaticsLibrary::Approach(float start, float end, float shift)
{
	//Store start value
	float a = start;

	if (start < end)
	{
		a = FMath::Min(start + shift, end);
		if (a > end)
		{
			a = end;
			return a;
		}
		return a;
	}
	else if (start > end)
	{
		a = FMath::Max(start - shift, end);
		if (a < end)
		{
			a = end;
			return a;
		}
		return a;
	}
	return a;
}

void UStaticsLibrary::RandomizeVector(FVector InVector, FVector& OutVector)
{
	FVector TV;
	TV.X = FMath::RandRange(-InVector.X, InVector.X);
	TV.Y = FMath::RandRange(-InVector.Y, InVector.Y);
	TV.Z = FMath::RandRange(-InVector.Z, InVector.Z);

	OutVector = TV;
}

void UStaticsLibrary::GetPlayer(bool& bPlayerValid, AActor*& Player)
{
	bPlayerValid = true;

	if (GetWorld() == nullptr)
	{
		bPlayerValid = false;
		return;
	}

	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Pawn == nullptr)
	{
		bPlayerValid = false;
		return;
	}

	Player = Pawn;
}