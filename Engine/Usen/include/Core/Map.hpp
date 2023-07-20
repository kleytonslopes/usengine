/*********************************************************************
 *   File: Map.h
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MAP_HPP
#define	US_MAP_HPP

#include <map>
#include <tuple>
#include <string>

template<typename TKey, typename TValue>
class Pair
{
public:
	TKey& key;
	TValue& value;

	Pair(TKey& key, TValue& value) : key{key}, value{value}
	{

	}

};

template<class TKey, class TValue>
class Map
{
public:
	Map() = default;

	void Add(const TKey& key, const TValue value)
	{
		collection[key] = value;
	}

	uint32 Size()
	{
		return collection.size();
	}

	
	TValue& Get(TKey key)
	{
		return collection[key];
	}

	//TVector<TValue&> Data()
	//{
	//	TVector<TValue*> ref;
	//	ref.resize(collection.Size());

	//	for (auto& it : collection)
	//	{
	//		ref.emplace(it);
	//	}
	//	return ref;
	//}

private:
	std::map<TKey, TValue> collection;
};

#endif // !US_MAP_HPP
