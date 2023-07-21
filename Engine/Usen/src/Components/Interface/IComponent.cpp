#include "upch.hpp"
#include "Components/Interface/IComponent.hpp"
#include "Core/Guid.hpp"
#include "Framework/Entity.hpp"

IComponent::IComponent(UEntity* Owner) 
	: Owner{ Owner }
{
	Id = FGuid::NewGuid();
}

IComponent::~IComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("Component '%s' Destroyed!", Id.c_str()));
}
