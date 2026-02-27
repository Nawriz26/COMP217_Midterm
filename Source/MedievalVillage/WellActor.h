#pragma once

#include "CoreMinimal.h"
#include "VillageActor.h"
#include "WellActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class MEDIEVALVILLAGE_API AWellActor : public AVillageActor
{
	GENERATED_BODY()

public:
	AWellActor();

	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Well|Components")
	UStaticMeshComponent* BucketMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Well|Interaction")
	float BucketRotateStepDegrees = 45.0f;
};