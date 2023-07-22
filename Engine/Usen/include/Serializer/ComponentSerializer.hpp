/*********************************************************************
 *   File: ComponentSerializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_COMPONENT_SERIALIZER_HPP
#define	US_COMPONENT_SERIALIZER_HPP

#include "Serializer/Serializer.hpp"


class IComponent;

class UComponentSerializer : public USerializer
{
	DEFAULT_BODY(USerializer);
public:
	explicit UComponentSerializer(IComponent* component);
	~UComponentSerializer() final;

	void Serialize() override;
	void Serialize(YAML::Emitter& otherOut) override;
	bool Deserialize(const FString& scenePath) override;

private:
	IComponent* Component = nullptr;
};

#endif // !US_COMPONENT_SERIALIZER_HPP