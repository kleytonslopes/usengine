#include "upch.hpp"
#include "Components/MeshComponent.hpp"
#include "Framework/Entity.hpp"

void UMeshComponent::Initialize()
{
	/* Load Model */
}

void UMeshComponent::SetMeshParameters(const FMeshParameters& parameters)
{
	this->parameters = parameters;
}
