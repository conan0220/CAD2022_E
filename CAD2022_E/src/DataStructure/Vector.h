#pragma once

#include <iostream>

template <typename T>
class Vector
{
public:
	// constructor
	Vector(const int sz = 0);
	~Vector() { delete[] self; }

	// useful function
	const T* begin() const { return self; }
	const T* end() const { return self + size; }

	const int& GetSize() const { return size; }
	const int& GetCapacity() const { return capacity; }
	bool IsEmpty() const { return size == 0; }

	void PushBack(const T& element);
	void Resize(const int& sz);
	void Expand(const int& sz);
	void Reverse();
	void RemoveAll() { Resize(0); }
	void RemoveAt(const int& index);
	void RemoveLast();

	void BubbleSort();
	void QuickSort();

	// operator
	T& operator [] (const int& n) const;
	void operator += (const T& element) { PushBack(element); }
	void operator = (const Vector<T>& arr);
	void operator *= (const int& time);
	void operator += (const Vector<T>& arr) { *this = *this + arr; }

private:
	void AllocateMemory(const int& cap);
	int CalculateCapacity(const int& sz) const;

	void SubQuickSort(int left_index, int right_index);
	void Swap(T& a, T& b);

	// operator
	Vector<T>& operator + (const Vector<T>& arr);

	T* self = nullptr;	// the space of array
	int capacity = 0;
	int size = 0;
};

template <typename T>
Vector<T>::Vector(const int sz)
{
	AllocateMemory(CalculateCapacity(sz));
	size = sz;
}

template <typename T>
void Vector<T>::PushBack(const T& element)
{
	if (size + 1 > capacity)
	{
		Expand(size + 1);
	}
	else
	{
		size += 1;
	}
	self[size - 1] = element;
}

template <typename T>
void Vector<T>::Resize(const int& sz)
{
	AllocateMemory(CalculateCapacity(sz));
	size = sz;
}

template <typename T>
void Vector<T>::Expand(const int& sz)
{
	if (sz < size)
	{
		std::cerr << "[Error]: Failed to Expand, don't less than size" << std::endl;
		exit(EXIT_FAILURE);
	}
	else if (capacity >= sz)
	{
		size = sz;
	}
	else
	{
		T* temp;
		temp = new T[size]();
		for (int i = 0; i < size; i++)
		{
			temp[i] = self[i];
		}
		AllocateMemory(CalculateCapacity(sz));
		for (int i = 0; i < size; i++)
		{
			self[i] = temp[i];
		}
		delete[] temp;
		size = sz;
	}
}

template<typename T>
inline void Vector<T>::Reverse()
{
	for (int i = 0; i < GetSize() / 2; i++)
	{
		Swap(self[i], self[(GetSize() - 1) - i]);
	}
}

template<typename T>
void Vector<T>::RemoveAt(const int& index)
{
	if (index >= this->size)
	{
		std::cerr << "[Error]: Index out of range" << std::endl;
		exit(EXIT_FAILURE);
	}

	Vector<T> temp;
	temp = *this;
	this->RemoveAll();
	for (int i = 0; i < temp.GetSize(); i++)
	{
		if (i != index)
			*this += temp[i];
	}
}

template<typename T>
inline void Vector<T>::RemoveLast()
{
	RemoveAt(size - 1);
}

template <typename T>
void Vector<T>::BubbleSort()
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (self[j] > self[j + 1])
			{
				Swap(self[j], self[j + 1]);
			}
		}
	}
}

template <typename T>
void Vector<T>::QuickSort()
{
	SubQuickSort(0, size - 1);
}

template <typename T>
void Vector<T>::SubQuickSort(int left_index, int right_index)
{
	if (left_index >= 0 && right_index < size && right_index - left_index > 0)
	{
		int i = left_index;
		int j = right_index;
		T standard = self[left_index];

		while (i != j)
		{
			while (self[j] >= standard && i < j)
			{
				j -= 1;		// move right pointer to left
			}
			while (self[i] <= standard && i < j)
			{
				i += 1;		// move left pointer to right
			}
			if (i < j) {	// when left is bigger than right then swap 
				Swap(self[i], self[j]);
			}
		}
		self[left_index] = self[i];
		self[i] = standard;

		SubQuickSort(left_index, i - 1);
		SubQuickSort(i + 1, right_index);
	}
}

template<typename T>
inline void Vector<T>::Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T& Vector<T>::operator [] (const int& n) const
{
	if (n >= size)
	{
		std::cerr << "[Error]: Index out of range" << std::endl;
		exit(EXIT_FAILURE);
	}
	return self[n];
}

template <typename T>
void Vector<T>::operator = (const Vector<T>& arr)
{
	this->RemoveAll();
	for (const T& element : arr)
	{
		this->PushBack(element);
	}
}

template <typename T>
Vector<T>& Vector<T>::operator + (const Vector<T>& arr)
{
	static Vector<T> temp;
	temp.RemoveAll();
	for (const T& element : *this)
	{
		temp += element;
	}
	for (const T& element : arr)
	{
		temp += element;
	}
	return temp;
}

template<typename T>
void Vector<T>::operator*=(const int& time)
{
	Vector<T> temp;
	temp = *this;
	for (int i = 0; i < time - 1; i++)
	{
		*this += temp;
	}
}

template <typename T>
void Vector<T>::AllocateMemory(const int& cap)
{
	if (cap < 0)
	{
		std::cerr << "[Error]: Failed to allocate memory" << std::endl;
		exit(EXIT_FAILURE);
	}
	else if (self != nullptr)
	{
		delete[] self;
	}
	capacity = cap;
	self = new T[cap]();
}

template <typename T>
int Vector<T>::CalculateCapacity(const int& sz) const
{
	if (sz < 0)
	{
		std::cerr << "[Error]: Invalid Size" << std::endl;
		exit(EXIT_FAILURE);
	}
	else if (sz == 0)
	{
		return 0;
	}

	int cap = 1;
	while (cap < sz)
	{
		cap *= 2;
	}
	return cap;
}