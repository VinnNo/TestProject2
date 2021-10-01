// Oh, boy. Here we go!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectMacros.h"
#include "PickupBase.generated.h"

UCLASS()
class TESTPROJECT2_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GemMesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Sight;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class URotatingMovementComponent* RotatingMovement;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ValueRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TSet<UStaticMesh*> MeshList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TSet<UMaterialInstance*> MaterialList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UStaticMesh* RandomMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UMaterialInstance* RandomMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int RandomValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector RandomScale;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ScaleRange = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bFoundPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float SpeedStart = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float Speed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float SpeedMax = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float SpeedScale = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float RandomRotationSpeed = 500.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShieldSpeedMultiplier = 3.0f;






protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
		void RandomizeAll();

	UFUNCTION(BlueprintCallable)
		void SetPlayerFound(bool bFound);

	UFUNCTION(BlueprintCallable)
		void SetRotation();

	UFUNCTION(BlueprintImplementableEvent)
		void OnRandomized();

	void MoveToTarget(float Delta);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
