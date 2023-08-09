/*********************************************************************
 *   File: UniquePtr.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_UNIQUE_PTR_HPP
#define	US_UNIQUE_PTR_HPP

#include "Core/Core.hpp"
#include "Core/ClassOf.hpp"
#include <memory>

template<typename T>
class UUniquePtr
{
public:
	UUniquePtr() = default;

	template<typename ... Args>
	static UUniquePtr<T> Make(Args... args);
	static UUniquePtr<T> Make();
	//static UUniquePtr<T> MakeCast();
	template<typename U>
	static inline UUniquePtr<T> MakeCast()
	{
		std::unique_ptr<T> ptrm = std::make_unique<U>();
		return UUniquePtr<T>(std::move(ptrm));
	}

	template<typename U>
	static UUniquePtr<T> FromClass(TClassOf<U>& otherClass)
	{
		//std::unique_ptr<T> ptrm = std::make_unique<U>();
		return UUniquePtr<U>(std::move(otherClass.Class));
	}

	UUniquePtr<T> Move();
	void Destroy();

	T* Get() { return ptr.get(); }

	operator T* () { return ptr.get(); }

private:
	UUniquePtr(std::unique_ptr<T> nptr);
	std::unique_ptr<T> ptr;
};

template<typename T>
inline UUniquePtr<T>::UUniquePtr(std::unique_ptr<T> nptr)
	: ptr{ std::move(nptr) }
{

}

template<typename T>
inline UUniquePtr<T> UUniquePtr<T>::Make()
{
	std::unique_ptr<T> ptrm = std::make_unique<T>();
	return UUniquePtr<T>(std::move(ptrm));
}

//template<typename T>
//inline UUniquePtr<T> UUniquePtr<T>::MakeCast()
//{
//	std::unique_ptr<T> ptrm = std::make_unique<T>();
//	return UUniquePtr<T>(std::move(ptrm));
//}

template<typename T>
inline UUniquePtr<T> UUniquePtr<T>::Move()
{
	return UUniquePtr<T>(std::move(ptr));
}

template<typename T>
inline void UUniquePtr<T>::Destroy()
{
	ptr.reset();
}

template<typename T>
template<typename ...Args>
inline UUniquePtr<T> UUniquePtr<T>::Make(Args ...args)
{
	std::unique_ptr<T> ptrm = std::make_unique<T>(args ...);
	return UUniquePtr<T>(std::move(ptrm));
}

#endif // !US_UNIQUE_PTR_HPP