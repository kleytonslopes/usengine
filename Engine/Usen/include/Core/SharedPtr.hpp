/*********************************************************************
 *   File: SharedPtr.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SHARED_PTR_HPP
#define	US_SHARED_PTR_HPP

#include "Core/MinimalCore.hpp"
#include "Core/ClassOf.hpp"
#include <memory>

template<typename T>
class USharedPtr
{
public:
	USharedPtr() = default;

	template<typename ... Args>
	static USharedPtr<T> Make(Args... args);
	static USharedPtr<T> Make();

	template<typename U>
	static USharedPtr<T> FromClass(TClassOf<U>& otherClass)
	//static USharedPtr<T> FromClass(TClassOf<U>&& otherClass)
	{
		//std::unique_ptr<T> ptrm = std::make_unique<U>();
		return USharedPtr<U>(otherClass.Class);
	}

	T* Get() { return ptr.get(); }

	USharedPtr<T> Move();
	void Destroy();

	operator T* () { return ptr.get(); }

	//template<typename U>
	//operator USharedPtr<U>() 
	//{ 
	//	return USharedPtr<T>(std::make_shared<T>());
	//}

private:
	USharedPtr(std::shared_ptr<T>& nptr);
	std::shared_ptr<T> ptr;
};

template<typename T>
inline USharedPtr<T> USharedPtr<T>::Move()
{
	return USharedPtr<T>(std::move(ptr));
}

template<typename T>
inline void USharedPtr<T>::Destroy()
{
	ptr.reset();
}

template<typename T>
inline USharedPtr<T>::USharedPtr(std::shared_ptr<T>& nptr)
	: ptr{ nptr }
{

}

template<typename T>
template<typename ...Args>
inline USharedPtr<T> USharedPtr<T>::Make(Args ...args)
{
	return USharedPtr<T>(std::make_shared<T>(args ...));
}

template<typename T>
inline USharedPtr<T> USharedPtr<T>::Make()
{
	return USharedPtr<T>(std::make_shared<T>());
}

#endif // !US_SHARED_PTR_HPP