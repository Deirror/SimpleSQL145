#pragma once
#include "PolymorphicPointer.hpp"
#include "Vector.hpp"

template <class T>
class PolymorphicContainer
{
private:
	Vector<PolymorphicPointer<T>> _collection;

public:
	PolymorphicContainer() = default;

	PolymorphicContainer(size_t size, const PolymorphicPointer<T>& instantiateWith);

	bool containsAt(size_t index) const;
	void removeAt(size_t index);

	void pushBack(const PolymorphicPointer<T>& obj);

	void setAtIndex(const PolymorphicPointer<T>& obj, size_t index);

	size_t getSize() const;
	size_t getCapacity() const;

	const PolymorphicPointer<T>& operator[](size_t index) const;
	PolymorphicPointer<T>& operator[](size_t index);
};

template<class T>
PolymorphicContainer<T>::PolymorphicContainer(size_t size, const PolymorphicPointer<T>& instantiateWith)
	: _collection(size, instantiateWith)
{
}

template<class T>
bool PolymorphicContainer<T>::containsAt(size_t index) const
{
	return (_collection[index] != nullptr);
}

template<class T>
void PolymorphicContainer<T>::removeAt(size_t index)
{
	_collection.removeAt(index);
}

template<class T>
void PolymorphicContainer<T>::pushBack(const PolymorphicPointer<T>& obj)
{
	_collection.pushBack(obj);
}

template<class T>
void PolymorphicContainer<T>::setAtIndex(const PolymorphicPointer<T>& obj, size_t index)
{
	_collection.setAtIndex(obj, index);
}

template<class T>
size_t PolymorphicContainer<T>::getSize() const
{
	return _collection.getSize();
}

template<class T>
size_t PolymorphicContainer<T>::getCapacity() const
{
	return _collection.getCapacity();
}

template<class T>
const PolymorphicPointer<T>& PolymorphicContainer<T>::operator[](size_t index) const
{
	return _collection[index];
}

template<class T>
PolymorphicPointer<T>& PolymorphicContainer<T>::operator[](size_t index)
{
	return _collection[index];
}
