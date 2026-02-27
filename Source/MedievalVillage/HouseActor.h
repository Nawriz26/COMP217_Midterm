#pragma once

#include "CoreMinimal.h"
#include "VillageActor.h"
#include "HouseActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class MEDIEVALVILLAGE_API AHouseActor : public AVillageActor
{
	GENERATED_BODY()

public:
	AHouseActor();

	virtual void UpdateAppearance_Implementation(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "House|Components")
	UStaticMeshComponent* RoofMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "House|Components")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "House|Components")
	TArray<UStaticMeshComponent*> WindowMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "House|Windows")
	int32 WindowCount = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "House|Windows")
	float NightGlowStrength = 15.0f;
};