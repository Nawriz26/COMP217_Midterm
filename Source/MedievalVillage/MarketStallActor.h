#pragma once

#include "CoreMinimal.h"
#include "VillageActor.h"
#include "MarketStallActor.generated.h"

class UStaticMeshComponent;
//class UPointLightComponent* Light;

UCLASS()
class MEDIEVALVILLAGE_API AMarketStallActor : public AVillageActor
{
	GENERATED_BODY()

public:
	AMarketStallActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stall|Components")
	UStaticMeshComponent* TableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stall|Components")
	UStaticMeshComponent* CanopyMesh;

};