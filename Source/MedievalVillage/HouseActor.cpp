#include "HouseActor.h"

#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

AHouseActor::AHouseActor()
{
	// Load Engine Basic Shapes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshObj(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMeshObj(TEXT("/Engine/BasicShapes/Cone.Cone"));

	if (CubeMeshObj.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMeshObj.Object);
		Mesh->SetRelativeScale3D(FVector(6.0f, 6.0f, 4.0f)); // big house body
	}

	RoofMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoofMesh"));
	RoofMesh->SetupAttachment(Root);
	if (ConeMeshObj.Succeeded())
	{
		RoofMesh->SetStaticMesh(ConeMeshObj.Object);
		RoofMesh->SetRelativeLocation(FVector(0, 0, 420));      // sits on top
		RoofMesh->SetRelativeScale3D(FVector(7.0f, 7.0f, 2.0f));
	}

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(Root);
	if (CubeMeshObj.Succeeded())
	{
		DoorMesh->SetStaticMesh(CubeMeshObj.Object);
		DoorMesh->SetRelativeLocation(FVector(300, 0, 80));
		DoorMesh->SetRelativeScale3D(FVector(0.8f, 1.5f, 1.6f));
	}

	// Create windows in a loop (required: loops)
	WindowMeshes.Reserve(WindowCount);
	for (int32 i = 0; i < WindowCount; i++)
	{
		const FName CompName(*FString::Printf(TEXT("Window_%d"), i));
		UStaticMeshComponent* Window = CreateDefaultSubobject<UStaticMeshComponent>(CompName);
		Window->SetupAttachment(Root);

		if (CubeMeshObj.Succeeded())
		{
			Window->SetStaticMesh(CubeMeshObj.Object);
		}

		Window->SetRelativeScale3D(FVector(0.6f, 0.2f, 0.6f));

		// Place windows: two on front, two on sides (simple pattern)
		if (i == 0) Window->SetRelativeLocation(FVector(260, -140, 220));
		if (i == 1) Window->SetRelativeLocation(FVector(260, 140, 220));
		if (i == 2) Window->SetRelativeLocation(FVector(0, 260, 220));
		if (i == 3) Window->SetRelativeLocation(FVector(0, -260, 220));

		WindowMeshes.Add(Window);
	}

	// House doesn’t need point light by default
	Light->SetVisibility(false);
	Light->SetIntensity(0.0f);
}

void AHouseActor::UpdateAppearance_Implementation(float DeltaTime)
{
	// Conditional day/night behavior (required: conditionals)
	// Fake “night” if time is in second half of a 20-second cycle.
	const float T = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	const bool bNight = FMath::Fmod(T, 20.0f) > 10.0f;

	// If we have a dynamic material, tint house slightly at night
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"),
			bNight ? FLinearColor(0.25f, 0.25f, 0.30f) : FLinearColor(0.55f, 0.45f, 0.35f));
		DynamicMaterial->SetScalarParameterValue(TEXT("EmissiveStrength"), bNight ? 0.0f : 0.0f);
	}

	// “Glow” windows at night by setting emissive on each window material
	for (UStaticMeshComponent* W : WindowMeshes)
	{
		if (!W) continue;
		UMaterialInstanceDynamic* WinDyn = W->CreateAndSetMaterialInstanceDynamic(0);
		if (!WinDyn) continue;

		WinDyn->SetVectorParameterValue(TEXT("BaseColor"),
			bNight ? FLinearColor(1.0f, 0.85f, 0.3f) : FLinearColor(0.08f, 0.08f, 0.10f));

		WinDyn->SetScalarParameterValue(TEXT("EmissiveStrength"),
			bNight ? NightGlowStrength : 0.0f);
	}
}