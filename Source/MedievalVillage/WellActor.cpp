#include "WellActor.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AWellActor::AWellActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeObj(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (CylinderObj.Succeeded())
	{
		Mesh->SetStaticMesh(CylinderObj.Object);
		Mesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 1.5f));
	}

	BucketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BucketMesh"));
	BucketMesh->SetupAttachment(Root);
	if (CubeObj.Succeeded())
	{
		BucketMesh->SetStaticMesh(CubeObj.Object);
		BucketMesh->SetRelativeLocation(FVector(200, 0, 220));
		BucketMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	}

	Light->SetVisibility(false);
	Light->SetIntensity(0.0f);
}

void AWellActor::Interact_Implementation(AActor* Interactor)
{
	// Required: runtime interaction using getter/setter
	FRotator R = GetActorRotationCustom();
	R.Yaw += BucketRotateStepDegrees;
	SetActorRotationCustom(R);

	// Also rotate bucket for visual feedback
	if (BucketMesh)
	{
		FRotator B = BucketMesh->GetRelativeRotation();
		B.Roll += BucketRotateStepDegrees;
		BucketMesh->SetRelativeRotation(B);
	}
}