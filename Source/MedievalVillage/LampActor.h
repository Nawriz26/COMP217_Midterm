#pragma once

#include "CoreMinimal.h"
#include "VillageActor.h"
#include "LampActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class MEDIEVALVILLAGE_API ALampActor : public AVillageActor
{
	GENERATED_BODY()

public:
	ALampActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lamp|Components")
	UStaticMeshComponent* LampHeadMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lamp|Light")
	float BaseIntensity = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lamp|Light")
	float PulseAmplitude = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lamp|Light")
	float PulseSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lamp|State")
	bool bLampOn = true;
};