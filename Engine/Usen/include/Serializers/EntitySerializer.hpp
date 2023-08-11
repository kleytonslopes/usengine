/*********************************************************************
 *   File: EntitySerializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ENTITY_SERIALIZER_HPP
#define	US_ENTITY_SERIALIZER_HPP


#include "Serializers/Serializer.hpp"
#include "EntitySerializer-generated.hpp"

class AEntity;

class FEntitySerializer : public BSerializer
{
	DEFAULT_BODY_GENERATED()
public:
	void Serialize() override;
	void Serialize(SeriFile& otherOut) override;
	bool Deserialize(const FString& scenePath) override;

	void SetEntity(AEntity* entity);
private:
	AEntity* Entity = nullptr;

	void SerializeComponents(SeriFile& otherOut);
};

#endif // !US_ENTITY_SERIALIZER_HPP