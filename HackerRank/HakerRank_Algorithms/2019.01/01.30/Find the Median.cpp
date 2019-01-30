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

vector<int> closestNumbers(vector<int> arr) {
	vector<int> answer;
	sort(arr.begin(), arr.end());
	int minvalue = arr[1] - arr[0];
	for (int i = 1; i < arr.size(); i++) {
		int value = arr[i] - arr[i-1];
		if (value == minvalue) {
			answer.push_back(arr[i - 1]);
			answer.push_back(arr[i]);
		}
		else if (value < minvalue) {
			answer.clear();
			answer.push_back(arr[i - 1]);
			answer.push_back(arr[i]);
			minvalue = value;
		}
	}
	return answer;
}

int main()
{
	vector<int> value;
	int repeatNum = 0;
	cin >> repeatNum;
	for (int i = 0; i < repeatNum; i++) {
		int number;
		cin >> number;
		value.push_back(number);
	}
	value = closestNumbers(value);
	for (int i = 0; i < value.size(); i++)cout << value[i]<<" ";
	return 0;
}
