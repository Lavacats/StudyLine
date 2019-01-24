// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <list>
#include <math.h>
using namespace std;


vector<int> quickSort(vector<int> arr) {
	vector<int> firstLine;
	vector<int> lastLine;
	for (int i = 1; i < arr.size(); i++) {
		if (arr[0] > arr[i])firstLine.push_back(arr[i]);
		else if (arr[0] < arr[i])lastLine.push_back(arr[i]);
	}
	firstLine.push_back(arr[0]);
	for (int i = 0; i < lastLine.size(); i++) {
		firstLine.push_back(lastLine[i]);
	}
	return firstLine;
}


int main()
{
	insertionSort1(6, { 1,4,3,5,6,2 });

	return 0;
}

