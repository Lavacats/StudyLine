#include "pch.h"
#include "MyVector.h"

MyVector::MyVector(int capacity)
{
	_vectorSize = 0;
	_vectorCapacity = capacity;
	VectorObject = new MyObject[capacity];
}

MyVector::MyVector(const MyVector & other)
{
	_vectorSize = other._vectorSize;
	_vectorCapacity = other._vectorCapacity;
	VectorObject = other.VectorObject;
}

MyVector & MyVector::operator=(const MyVector & other)
{
	_vectorSize = other._vectorSize;
	_vectorCapacity = other._vectorCapacity;
	VectorObject = other.VectorObject;
	return *this;
}

MyVector::~MyVector()
{
	_vectorSize = 0;
	_vectorCapacity = 0;
	delete[] VectorObject;
	VectorObject = NULL;
}

int MyVector::GetCapacity() const
{
	return _vectorCapacity;
}

int MyVector::GetSize() const
{
	return _vectorSize;
}

void MyVector::Add(int id)
{
	if (_vectorSize == _vectorCapacity) {
		MyObject* saveValue = new MyObject[_vectorSize ];
		for (int i = 0; i < _vectorCapacity; i++) {
			saveValue[i] = VectorObject[i];
		}
		VectorObject = new MyObject[_vectorSize * 2];
		for (int i = 0; i < _vectorCapacity; i++) {
			VectorObject[i] = saveValue[i];
		}
		delete[] saveValue;
		_vectorCapacity = _vectorSize * 2;
	}
	VectorObject[_vectorSize++]._id = id;
}

void MyVector::TrimToSize()
{
	MyObject* saveValue = new MyObject[_vectorSize];
	for (int i = 0; i < _vectorSize; i++) {
		saveValue[i] = VectorObject[i];
	}

	VectorObject = new MyObject[_vectorSize];
	for (int i = 0; i < _vectorSize; i++) {
		VectorObject[i] = saveValue[i];
	}
	_vectorCapacity = _vectorSize;
	delete[] saveValue;
}

MyObject & MyVector::operator[](size_t index)
{
	return VectorObject[index];
}

std::string MyVector::ToString() const
{
	std::string VectorToString;
	for (int i = 0; i < _vectorSize; i++) {
		VectorToString += (std::to_string(VectorObject[i]._id) + " ");
	}
	return VectorToString;
}

void MyVector::Sort()
{
	QuickSort(VectorObject, 0, _vectorSize-1);
}

int MyVector::Partition(MyObject* arr, int left, int right)
{
	int pivot = arr[left]._id;
	int low = left + 1;
	int high = right;

	while (low <= high){
		int value1 = arr[low]._id;
		while (pivot > value1&& low <= right) {
			low++;
			value1 = arr[low]._id;
		}

		int value2 = arr[high]._id;
		while (pivot < value2 && high >= (left + 1)) {
			high--;
			value2 = arr[high]._id;
		}

		if (low <= high) {
			int temp = arr[low]._id;
			arr[low]._id = arr[high]._id;
			arr[high]._id = temp;
		}
	}
	int lowValue = arr[left]._id;
	int highValue = arr[high]._id;
	int temp = lowValue;
	arr[left]._id = highValue;
	arr[high]._id = temp;

	return high;			
}

void MyVector::QuickSort(MyObject* arr, int left, int right)
{
	if (left <= right){
		int pivot = Partition(arr, left, right);	
		QuickSort(arr, left, pivot - 1);			
		QuickSort(arr, pivot + 1, right);			
	}
}

MyObject * MyVector::FindById(int MyObjectId) const
{
	for (int i = 0; i < _vectorSize; i++) {
		if (VectorObject[i]._id == MyObjectId) {
			return &VectorObject[i];
		}
	}
	return nullptr;
}

MyVector * MyVector::GroupById(int * numGroups)
{
	MyVector newVector(*this);
	return &newVector;
}
