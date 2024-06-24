#pragma once
#include <cstring>
#include <stdexcept>
#include <utility>
#pragma warning (disable : 4996)
#define DEF_CAP 8

//The key is char array!!!
template <typename T>
class Dictionary
{
public:
	Dictionary();

	Dictionary(const Dictionary& other);
	Dictionary<T>& operator=(const Dictionary& other);

	Dictionary(Dictionary&& other) noexcept;
	Dictionary<T>& operator=(Dictionary&& other) noexcept;

	void add(const char* key, const T& object);

	void setKeyByIndex(const char* key, size_t index);
	void setValueByIndex(const T& obj, size_t index);

	void changeKey(const char* oldKey, const char* newKey);

	void removeByKey(const char* key);
	const T& getByKey(const char* key) const;

	int contains(const char* key) const;
	bool isEmpty() const;
	void clear();

	size_t getSize() const;
	size_t getCapacity() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	const char* getKeyByIndex(size_t index) const;

	~Dictionary();

private:
	struct Node
	{
		char* key = nullptr;
		T value;

		void setKey(const char* _key);
		void setValue(const T& object);
	};

	Node* nodes = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const Dictionary& other);
	void moveFrom(Dictionary&& other);

	void resize(size_t newCapacity);
};

template<typename T>
const T& Dictionary<T>::operator[](size_t index) const
{
	if (index >= size)
		throw std::invalid_argument("Out of range!");

	return nodes[index].value;
}

template<typename T>
Dictionary<T>::Dictionary() : size(0), capacity(DEF_CAP)
{
	nodes = new Node[capacity]{};
}

template<typename T>
Dictionary<T>::Dictionary(const Dictionary<T>& other)
{
	copyFrom(other);
}

template<typename T>
Dictionary<T>& Dictionary<T>::operator=(const Dictionary<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Dictionary<T>::Dictionary(Dictionary<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Dictionary<T>& Dictionary<T>::operator=(Dictionary<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
void Dictionary<T>::add(const char* _key, const T& object)
{
	if (!_key)
		throw std::invalid_argument("Nullptr");

	if (size == capacity)
		resize(capacity * 2);

	int index = contains(_key);

	if (index != -1)
		throw std::exception("Already contains element");

	nodes[size].setKey(_key);
	nodes[size].setValue(object);

	size++;
}

template<typename T>
void Dictionary<T>::setKeyByIndex(const char* key, size_t index)
{
	if (index >= size)
		throw std::invalid_argument("Out of range!");

	nodes[index].setKey(key);
}

template<typename T>
void Dictionary<T>::setValueByIndex(const T& obj, size_t index)
{
	if (index >= size)
		throw std::invalid_argument("Out of range!");

	nodes[index].setValue(obj);
}

template<typename T>
void Dictionary<T>::changeKey(const char* oldKey, const char* newKey)
{
	if (!oldKey || !newKey)
		throw std::invalid_argument("Nullptr");

	int index = contains(newKey);

	if (index != -1)
		throw std::invalid_argument("Already in the dictionary");

	index = contains(oldKey);

	if (index == -1)
		throw std::invalid_argument("Not found");

	nodes[index].setKey(newKey);
}

template<typename T>
void Dictionary<T>::Node::setKey(const char* _key)
{
	if (!_key)
		throw std::invalid_argument("Nullptr");

	delete[] key;
	key = new char[strlen(_key) + 1] {};

	strcpy(key, _key);
}

template<typename T>
void Dictionary<T>::Node::setValue(const T& object)
{
	value = object;
}

template<typename T>
void Dictionary<T>::free()
{
	for (int i = 0; i < size; i++)
	{
		delete[] nodes[i].key;
		nodes[i].key = nullptr;
	}

	delete[] nodes;

	nodes = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
void Dictionary<T>::copyFrom(const Dictionary<T>& other)
{
	size = other.size;
	capacity = other.capacity;

	nodes = new Node[capacity];

	for (int i = 0; i < size; i++)
	{
		nodes[i].setKey(other.nodes[i].key);
		nodes[i].setValue(other.nodes[i].value);
	}
}

template<typename T>
void Dictionary<T>::moveFrom(Dictionary<T>&& other)
{
	size = other.size;
	capacity = other.capacity;

	size = capacity = 0;

	nodes = other.nodes;
	other.nodes = nullptr;
}

template<typename T>
void Dictionary<T>::resize(size_t newCapacity)
{
	Node* newNodes = new Node[newCapacity];

	for (int i = 0; i < size; i++)
	{
		newNodes[i] = nodes[i];
	}

	delete[] nodes;
	nodes = newNodes;
	capacity = newCapacity;
}

template<typename T>
void Dictionary<T>::removeByKey(const char* key)
{
	if (!key)
		throw std::invalid_argument("Nullptr");

	int index = contains(key);

	if (index == -1)
		throw std::exception("Not found");

	if (size == capacity / 4 && capacity > DEF_CAP)
		resize(capacity / 2);

	for (int i = index; i < size - 1; i++)
	{
		nodes[i] = nodes[i + 1];
	}

	delete[] nodes[size].key;
	nodes[size].key = nullptr;
	size--;
}

template<typename T>
const T& Dictionary<T>::getByKey(const char* key) const
{
	if (!key)
		throw std::invalid_argument("Nullptr");

	int index = contains(key);

	if (index == -1)
		throw std::exception("Not found");

	return nodes[index].value;
}

template<typename T>
int Dictionary<T>::contains(const char* key) const
{
	if (!key)
		throw std::invalid_argument("Nullptr");

	for (int i = 0; i < size; i++)
	{
		if (strcmp(nodes[i].key, key) == 0)
			return i;
	}

	return -1;
}

template<typename T>
bool Dictionary<T>::isEmpty() const
{
	return (size == 0);
}

template<typename T>
void Dictionary<T>::clear()
{
	free();
	capacity = DEF_CAP;

	nodes = new Node[capacity];
}

template<typename T>
size_t Dictionary<T>::getSize() const
{
	return size;
}

template<typename T>
size_t Dictionary<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
T& Dictionary<T>::operator[](size_t index)
{
	if (index >= size)
		throw std::invalid_argument("Out of range!");

	return nodes[index].value;
}

template<typename T>
const char* Dictionary<T>::getKeyByIndex(size_t index) const
{
	return nodes[index].key;
}

template<typename T>
Dictionary<T>::~Dictionary()
{
	free();
}
