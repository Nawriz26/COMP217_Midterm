#include "MarketStallActor.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AMarketStallActor::AMarketStallActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeObj(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneObj(TEXT("/Engine/BasicShapes/Plane.Plane"));

	// Use base Mesh as “stall frame”
	if (CubeObj.Succeeded())
	{
		Mesh->SetStaticMesh(CubeObj.Object);
		Mesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 2.5f));
		Mesh->SetRelativeLocation(FVector(0, 0, 120));
	}

	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh"));
	TableMesh->SetupAttachment(Root);
	if (CubeObj.Succeeded())
	{
		TableMesh->SetStaticMesh(CubeObj.Object);
		TableMesh->SetRelativeScale3D(FVector(4.0f, 2.0f, 0.3f));
		TableMesh->SetRelativeLocation(FVector(0, 0, 60));
	}

	CanopyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CanopyMesh"));
	CanopyMesh->SetupAttachment(Root);
	if (PlaneObj.Succeeded())
	{
		CanopyMesh->SetStaticMesh(PlaneObj.Object);
		CanopyMesh->SetRelativeScale3D(FVector(3.0f, 2.0f, 1.0f));
		CanopyMesh->SetRelativeLocation(FVector(0, 0, 260));
		CanopyMesh->SetRelativeRotation(FRotator(0, 0, 0));
	}

	Light->SetVisibility(false);
	Light->SetIntensity(0.0f);
}