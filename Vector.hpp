#pragma once
#include <stdexcept>
#include "helperFunctions.h"
#define DEFAULT_CAPACITY 8

template<typename T>
class Vector
{
private:
	T* _collection = nullptr;

	size_t _size = 0;
	size_t _capacity = 0;

public:
	Vector();
	Vector(size_t size);

	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector(Vector&& other) noexcept;
	Vector& operator=(Vector&& other) noexcept;

	~Vector();

	void pushBack(const T& newElement);
	void pushBack(T&& newElement);

	void insertAtIndex(const T& newElement, size_t index);
	void insertAtIndex(T&& newElement, size_t index);

	void setAtIndex(const T& element, size_t index);
	void setAtIndex(T&& element, size_t index);

	void popBack();

	void removeAt(size_t index);

	size_t getCapacity() const;
	size_t getSize() const;
	bool isEmpty() const;

	bool contains(const T& element) const;

	int find(const T& element) const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

private:
	void free();
	void copyFrom(const Vector& other);

	void moveFrom(Vector&& other);

	void resize(size_t newCapacity);
};

template<typename T>
Vector<T>::Vector() : Vector(DEFAULT_CAPACITY)
{

}

template<typename T>
Vector<T>::Vector(size_t size) : _size(0)
{
	_capacity = roundToPowerOfTwo(size);
	_collection = new T[_capacity];
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] _collection;
}

template<typename T>
void Vector<T>::free()
{
	delete[] _collection;

	_collection = nullptr;

	_size = _capacity = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector& other)
{
	_size = other._size;
	_capacity = other._capacity;

	_collection = new T[_capacity];

	for (int i = 0; i < _size; i++)
	{
		_collection[i] = other._collection;
	}
}

template<typename T>
void Vector<T>::moveFrom(Vector&& other)
{
	_size = other._size;
	_capacity = other._capacity;

	other._size = other._capacity = 0;

	_collection = other._collection;

	other._collection = nullptr;
}

template<typename T>
void Vector<T>::resize(size_t size)
{
	size_t newCapacity = roundToPowerOfTwo(size);

	T* newCollection = new T[newCapacity];

	for (int i = 0; i < _size; i++)
		newCollection[i] = _collection[i];

	delete[] _collection;
	_collection = newCollection;

	_capacity = newCapacity;
}

template<typename T>
void Vector<T>::pushBack(const T& newElement)
{
	if (_size == _capacity)
		resize(_size + 1);

	_collection[_size++] = newElement;
}

template<typename T>
void Vector<T>::pushBack(T&& newElement)
{
	if (_size == _capacity)
		resize(_size + 1);

	_collection[_size++] = std::move(newElement);
}

template<typename T>
void Vector<T>::insertAtIndex(const T& newElement, size_t index)
{
	if (index > _size)
		throw std::out_of_range("Vector<T>::insertAtIndex out of range");

	if (_size == _capacity)
		resize(_size + 1);

	for (int i = _size - 1; i >= index; i++)
	{
		_collection[i + 1] = _collection[i];
	}

	_collection[index] = newElement;

	_size++;
}

template<typename T>
void Vector<T>::insertAtIndex(T&& newElement, size_t index)
{
	if (index > _size)
		throw std::out_of_range("Vector<T>::insertAtIndex out of range");

	if (_size == _capacity)
		resize(_size + 1);

	for (int i = _size - 1; i >= index; i--)
	{
		_collection[i + 1] = _collection[i];
	}

	_collection[index] = std::move(newElement);

	_size++;
}

template<typename T>
void Vector<T>::setAtIndex(const T& element, size_t index)
{
	if (index >= _size)
		throw std::out_of_range("Vector<T>::operator[] out of range");

	_collection[index] = element;
}

template<typename T>
void Vector<T>::setAtIndex(T&& element, size_t index)
{
	if (index >= _size)
		throw std::out_of_range("Vector<T>::operator[] out of range");

	_collection[index] = std::move(element);
}

template<typename T>
void Vector<T>::popBack()
{
	if (_size == 0)
		throw std::out_of_range("Vector<T>::popBack empty");

	_size--;

	if (_size * 4 == _capacity && _capacity > DEFAULT_CAPACITY)
		resize(_size);
}

template<typename T>
void Vector<T>::removeAt(size_t index)
{
	if (index > _size)
		throw std::out_of_range("Vector<T>::removeAt out of range or empty");

	for (int i = index; i < _size - 1; i++)
	{
		_collection[i] = _collection[i + 1];
	}

	_size--;

	if (_size * 4 == _capacity && _capacity > DEFAULT_CAPACITY)
		resize(_size);
}

template<typename T>
size_t Vector<T>::getCapacity() const
{
	return _capacity;
}

template<typename T>
size_t Vector<T>::getSize() const
{
	return _size;
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return(_size == 0);
}

template<typename T>
bool Vector<T>::contains(const T& element) const
{
	return (find(element) != -1);
}

template<typename T>
int Vector<T>::find(const T& element) const
{
	int index = -1;

	for (int i = 0; i < _size; i++)
	{
		if (_collection[i] == element)
		{
			index = i;
			break;
		}
	}

	return index;
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
	if (index >= _size)
		throw std::out_of_range("Vector<T>::operator[] out of range");

	return _collection[index];
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
	if (index >= _size)
		throw std::out_of_range("Vector<T>::operator[] out of range");

	return _collection[index];
}