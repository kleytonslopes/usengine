/*********************************************************************
 *   File: SharedPtr.hpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_SHARED_PTR_HPP
#define	US_SHARED_PTR_HPP

#include <memory>

template<typename T>
class USharedPtr
{
public:
	USharedPtr() = default;

	template<typename ... Args>
	static USharedPtr<T> Make(Args... args);
	static USharedPtr<T> Make();

	T* Get() { return ptr.get(); }

	USharedPtr<T> Move();
	void Destroy();

	operator T* () { return ptr.get(); }

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