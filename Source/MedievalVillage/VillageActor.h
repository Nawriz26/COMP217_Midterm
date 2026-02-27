#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VillageActor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UPointLightComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;

UCLASS()
class MEDIEVALVILLAGE_API AVillageActor : public AActor
{
	GENERATED_BODY()

public:
	AVillageActor();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	virtual void Tick(float DeltaTime) override;

	// === Components (required by your spec) ===
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Village|Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Village|Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Village|Components")
	UPointLightComponent* Light;

	// === Variables (required by your spec) ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Village|Transform")
	FVector ActorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Village|Transform")
	FRotator ActorRotation;

	// If true, OnConstruction will apply ActorLocation/ActorRotation to the real Actor transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Village|Transform")
	bool bUseCustomTransform = true;

	// Optional: assign a base material in Blueprint; we’ll create a dynamic instance at runtime
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Village|Materials")
	UMaterialInterface* BaseMaterial;

	// Created at runtime
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Village|Materials")
	UMaterialInstanceDynamic* DynamicMaterial;

	// === Setter / Getter (required) ===
	UFUNCTION(BlueprintCallable, Category = "Village|Transform")
	void SetActorLocationCustom(FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Village|Transform")
	FVector GetActorLocationCustom() const;

	UFUNCTION(BlueprintCallable, Category = "Village|Transform")
	void SetActorRotationCustom(FRotator NewRotation);

	UFUNCTION(BlueprintCallable, Category = "Village|Transform")
	FRotator GetActorRotationCustom() const;

	// === Polymorphism (required) ===
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Village|Interaction")
	void Interact(AActor* Interactor);
	virtual void Interact_Implementation(AActor* Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Village|Appearance")
	void UpdateAppearance(float DeltaTime);
	virtual void UpdateAppearance_Implementation(float DeltaTime);

protected:
	void ApplyCustomTransformToActor();
	void SyncCustomVarsFromActor();
};