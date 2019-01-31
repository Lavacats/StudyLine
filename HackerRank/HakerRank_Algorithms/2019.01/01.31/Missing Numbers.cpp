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

vector<int> missingNumbers(vector<int> arr, vector<int> brr) {
	sort(arr.begin(), arr.end());
	sort(brr.begin(), brr.end());
	vector<int> firstArray;
	vector<int> secondArray;
	int value = arr[0];
	firstArray.push_back(value);
	for (int i = 0; i < arr.size(); i++) {
		if (value != arr[i]) {
			value = arr[i];
			firstArray.push_back(value);
		}
	}
	value = brr[0];
	secondArray.push_back(value);
	for (int i = 0; i < brr.size(); i++) {
		if (value != brr[i]) {
			value = brr[i];
			secondArray.push_back(value);
		}
	}
	vector<int> answer;
	int count = 0;
	for (int i = 0; i < firstArray.size(); i++) {
		if (firstArray[i] != secondArray[i + count]) {
			answer.push_back(brr[i + count]);
			count++;
			i--;
		}
	}

	return answer;
}


int main()
{
	missingNumbers({ 203,204,205,206,207,208,203,205,206,204 },
		{ 203,204,204,205,206,207,205,208,203,206,205,206,204 });

	return 0;
}
