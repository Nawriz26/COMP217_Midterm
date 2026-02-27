#include "VillageActor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AVillageActor::AVillageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);
	Light->SetIntensity(0.0f);      // default OFF
	Light->SetVisibility(false);    // default hidden for non-lamps

	// Defaults for your exposed vars
	ActorLocation = FVector::ZeroVector;
	ActorRotation = FRotator::ZeroRotator;

	BaseMaterial = nullptr;
	DynamicMaterial = nullptr;
}

void AVillageActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bUseCustomTransform)
	{
		ApplyCustomTransformToActor();
	}
	else
	{
		SyncCustomVarsFromActor();
	}
}

void AVillageActor::BeginPlay()
{
	Super::BeginPlay();

	// Ensure our custom vars reflect actual transform at runtime start
	if (!bUseCustomTransform)
	{
		SyncCustomVarsFromActor();
	}

	// Create a dynamic material instance if possible
	if (Mesh)
	{
		if (BaseMaterial)
		{
			DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BaseMaterial);
		}
		else
		{
			// If a material is already on the mesh, this creates a dynamic version of it
			DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
		}
	}
}

void AVillageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Default behavior: call UpdateAppearance so derived classes can override appearance logic
	UpdateAppearance(DeltaTime);
}

void AVillageActor::ApplyCustomTransformToActor()
{
	SetActorLocation(ActorLocation);
	SetActorRotation(ActorRotation);
}

void AVillageActor::SyncCustomVarsFromActor()
{
	ActorLocation = GetActorLocation();
	ActorRotation = GetActorRotation();
}

void AVillageActor::SetActorLocationCustom(FVector NewLocation)
{
	ActorLocation = NewLocation;
	SetActorLocation(ActorLocation);
}

FVector AVillageActor::GetActorLocationCustom() const
{
	return ActorLocation;
}

void AVillageActor::SetActorRotationCustom(FRotator NewRotation)
{
	ActorRotation = NewRotation;
	SetActorRotation(ActorRotation);
}

FRotator AVillageActor::GetActorRotationCustom() const
{
	return ActorRotation;
}

void AVillageActor::Interact_Implementation(AActor* Interactor)
{
	// Base does nothing. Derived actors override.
}

void AVillageActor::UpdateAppearance_Implementation(float DeltaTime)
{
	// Base does nothing. Derived actors override.
}