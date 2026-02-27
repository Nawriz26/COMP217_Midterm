#pragma once

#include "CoreMinimal.h"
#include "VillageActor.h"
#include "CartActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class MEDIEVALVILLAGE_API ACartActor : public AVillageActor
{
	GENERATED_BODY()

public:
	ACartActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cart|Components")
	UStaticMeshComponent* CartBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cart|Components")
	TArray<UStaticMeshComponent*> WheelMeshes;
};