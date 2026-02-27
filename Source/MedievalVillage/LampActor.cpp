#include "LampActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

ALampActor::ALampActor()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereObj(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	// Pole
	if (CylinderObj.Succeeded())
	{
		Mesh->SetStaticMesh(CylinderObj.Object);
		Mesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 4.0f));
		Mesh->SetRelativeLocation(FVector(0, 0, 200));
	}

	// Lamp head
	LampHeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LampHeadMesh"));
	LampHeadMesh->SetupAttachment(Root);
	if (SphereObj.Succeeded())
	{
		LampHeadMesh->SetStaticMesh(SphereObj.Object);
		LampHeadMesh->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
		LampHeadMesh->SetRelativeLocation(FVector(0, 0, 430));
	}

	// Light setup
	Light->SetVisibility(true);
	Light->SetIntensity(BaseIntensity);
	Light->SetRelativeLocation(FVector(0, 0, 430));
}

void ALampActor::BeginPlay()
{
	Super::BeginPlay();

	// Make dynamic material for lamp head too (so it can change color)
	if (LampHeadMesh)
	{
		LampHeadMesh->CreateAndSetMaterialInstanceDynamic(0);
	}
}

void ALampActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float T = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	if (bLampOn)
	{
		// Required: pulsing lamp intensity and changing mesh color
		const float Intensity = BaseIntensity + PulseAmplitude * FMath::Sin(T * PulseSpeed);
		Light->SetIntensity(Intensity);
		Light->SetVisibility(true);

		const uint8 Hue = (uint8)FMath::Fmod(T * 50.0f, 255.0f);
		const FLinearColor Color = FLinearColor::MakeFromHSV8(Hue, 255, 255);

		// Change base Mesh color if we have DynamicMaterial from base
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), Color);
			DynamicMaterial->SetScalarParameterValue(TEXT("EmissiveStrength"), 5.0f);
		}

		// Change lamp head color too
		if (LampHeadMesh)
		{
			if (UMaterialInstanceDynamic* HeadDyn = LampHeadMesh->CreateAndSetMaterialInstanceDynamic(0))
			{
				HeadDyn->SetVectorParameterValue(TEXT("BaseColor"), Color);
				HeadDyn->SetScalarParameterValue(TEXT("EmissiveStrength"), 20.0f);
			}
		}
	}
	else
	{
		Light->SetIntensity(0.0f);
		Light->SetVisibility(false);

		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(0.05f, 0.05f, 0.05f));
			DynamicMaterial->SetScalarParameterValue(TEXT("EmissiveStrength"), 0.0f);
		}
	}
}

void ALampActor::Interact_Implementation(AActor* Interactor)
{
	bLampOn = !bLampOn;
}