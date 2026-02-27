#include "CartActor.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ACartActor::ACartActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeObj(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

	// Base Mesh as a “handle” or frame
	if (CubeObj.Succeeded())
	{
		Mesh->SetStaticMesh(CubeObj.Object);
		Mesh->SetRelativeScale3D(FVector(2.0f, 0.3f, 0.3f));
		Mesh->SetRelativeLocation(FVector(-150, 0, 60));
	}

	CartBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CartBodyMesh"));
	CartBodyMesh->SetupAttachment(Root);
	if (CubeObj.Succeeded())
	{
		CartBodyMesh->SetStaticMesh(CubeObj.Object);
		CartBodyMesh->SetRelativeScale3D(FVector(2.5f, 1.5f, 0.8f));
		CartBodyMesh->SetRelativeLocation(FVector(50, 0, 80));
	}

	// Wheels (loop)
	WheelMeshes.Reserve(4);
	const FVector WheelLocs[4] =
	{
		FVector(150,  120, 30),
		FVector(150, -120, 30),
		FVector(-50,  120, 30),
		FVector(-50, -120, 30)
	};

	for (int32 i = 0; i < 4; i++)
	{
		const FName Name(*FString::Printf(TEXT("Wheel_%d"), i));
		UStaticMeshComponent* Wheel = CreateDefaultSubobject<UStaticMeshComponent>(Name);
		Wheel->SetupAttachment(Root);

		if (CylinderObj.Succeeded())
		{
			Wheel->SetStaticMesh(CylinderObj.Object);
		}
		Wheel->SetRelativeLocation(WheelLocs[i]);
		Wheel->SetRelativeRotation(FRotator(0, 0, 90));
		Wheel->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.2f));

		WheelMeshes.Add(Wheel);
	}

	Light->SetVisibility(false);
	Light->SetIntensity(0.0f);
}