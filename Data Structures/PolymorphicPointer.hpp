#pragma once
#include <utility>

template<typename T>
class PolymorphicPointer {
private:
	T* ptr = nullptr;

public:
	PolymorphicPointer() = default;
	PolymorphicPointer(T* ptr);

	PolymorphicPointer(const PolymorphicPointer<T>& other);
	PolymorphicPointer(PolymorphicPointer<T>&& other) noexcept;

	PolymorphicPointer<T>& operator=(const PolymorphicPointer<T>& other);
	PolymorphicPointer<T>& operator=(PolymorphicPointer<T>&& other) noexcept;

	~PolymorphicPointer();

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	T* get();
	const T* get() const;

	operator bool() const;

	void reset(T* ptr);
	T* release();

private:
	void free();
	void copyFrom(const PolymorphicPointer& other);
	void moveFrom(PolymorphicPointer&& other);
};


template<typename T>
PolymorphicPointer<T>::PolymorphicPointer(T* ptr) : ptr(ptr)
{ 
}

template<typename T>
PolymorphicPointer<T>::PolymorphicPointer(const PolymorphicPointer<T>& other) 
{
	copyFrom(other);
}

template<typename T>
PolymorphicPointer<T>::PolymorphicPointer(PolymorphicPointer<T>&& other) noexcept 
{
	moveFrom(std::move(other));
}

template<typename T>
PolymorphicPointer<T>& PolymorphicPointer<T>::operator=(const PolymorphicPointer<T>& other) 
{
	if (this != &other) 
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
PolymorphicPointer<T>& PolymorphicPointer<T>::operator=(PolymorphicPointer<T>&& other) noexcept 
{
	if (this != &other) 
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
PolymorphicPointer<T>::~PolymorphicPointer() 
{
	free();
}

template<typename T>
T* PolymorphicPointer<T>::operator->() 
{
	return ptr;
}

template<typename T>
const T* PolymorphicPointer<T>::operator->() const 
{
	return ptr;
}

template<typename T>
T& PolymorphicPointer<T>::operator*() {

	return *ptr;
}

template<typename T>
const T& PolymorphicPointer<T>::operator*() const 
{
	return *ptr;
}

template<typename T>
T* PolymorphicPointer<T>::get() {

	return ptr;
}

template<typename T>
const T* PolymorphicPointer<T>::get() const 
{
	return ptr;
}

template<typename T>
PolymorphicPointer<T>::operator bool() const
{
	return (ptr != nullptr);
}

template<typename T>
void PolymorphicPointer<T>::reset(T* ptr) 
{
	free();
	this->ptr = ptr;
}

template<typename T>
T* PolymorphicPointer<T>::release() 
{
	T* temp = ptr;

	ptr = nullptr;

	return temp;
}

template<typename T>
void PolymorphicPointer<T>::free() 
{
	delete ptr;
}

template<typename T>
void PolymorphicPointer<T>::copyFrom(const PolymorphicPointer& other) 
{ 
	ptr = other.ptr->clone();
}

template<typename T>
void PolymorphicPointer<T>::moveFrom(PolymorphicPointer&& other) 
{
	ptr = other.ptr;
	other.ptr = nullptr;
}