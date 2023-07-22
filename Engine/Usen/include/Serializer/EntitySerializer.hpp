/*********************************************************************
 *   File: EntitySerializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ENTITY_SERIALIZER_HPP
#define	US_ENTITY_SERIALIZER_HPP

#include "Serializer/Serializer.hpp"


class UEntity;

class UEntitySerializer : public USerializer
{
	DEFAULT_BODY(USerializer);
public:
	explicit UEntitySerializer(UEntity* entity);
	~UEntitySerializer() final;

	void Serialize() override;
	void Serialize(YAML::Emitter& otherOut) override;
	bool Deserialize(const FString& scenePath) override;

private:
	UEntity* Entity = nullptr;

	void SerializeComponents(YAML::Emitter& otherOut);
};

#endif // !US_ENTITY_SERIALIZER_HPP