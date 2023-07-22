/*********************************************************************
 *   File: IComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_COMPONENT_HPP
#define	US_COMPONENT_HPP

#include "Core/Core.hpp"
#include "Serializer/Serializer.hpp"

class UEntity;

class IComponent : public USerializer
{
public:
	IComponent(UEntity* Parent);
	virtual ~IComponent();

	virtual void Initialize();
	virtual void Update(float deltaTime) { /* override */ }
	virtual void Destroy() { /* override */ }

	bool CanTick() const { return bComponentTick; }
	UEntity* GetParent();
protected:
	FString Id;
	bool bComponentTick = false;

	UEntity* Parent = nullptr;


	virtual void Serialize() override {/* override */ }
	virtual void Serialize(YAML::Emitter& otherOut) override {/* override */ }
	virtual bool Deserialize(const FString& scenePath) override { return false; }

	void BeginComponentMap(YAML::Emitter& otherOut, const FString& componentName);

	friend class UEntitySerializer;
};

#endif // !US_COMPONENT_HPP