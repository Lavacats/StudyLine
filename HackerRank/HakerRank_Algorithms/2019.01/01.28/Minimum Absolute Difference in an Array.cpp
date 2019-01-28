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

int minimumAbsoluteDifference(vector<int> arr) {
	sort(arr.begin(), arr.end());
	int minNum = arr[1] - arr[0];
	for (int i = 1; i < arr.size(); i++) {
		int value = arr[i] - arr[i - 1];
		if (value < minNum) {
			minNum = value;
		}
	}
	return minNum;
}

int main()
{


	return 0;
}
