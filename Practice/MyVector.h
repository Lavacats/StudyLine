#pragma once

#include <string>

struct MyObject
{
	int _id;
};

class MyVector
{
private: 
	int _vectorSize;
	int _vectorCapacity;
	MyObject* VectorObject;

public: 

	MyVector(int capacity);

	MyVector(const MyVector& other);

	MyVector& operator=(const MyVector& other);

	~MyVector();

public: 

	int GetCapacity() const;

	int GetSize() const;

	void Add(int id);

	MyObject* FindById(int MyObjectId) const;

	void TrimToSize();

	MyObject& operator[](size_t index);

	std::string ToString() const;

	void Sort();

	MyVector* GroupById(int* numGroups);

	int Partition(MyObject* arr, int left, int right);
	void QuickSort(MyObject* arr, int left, int right);
};
