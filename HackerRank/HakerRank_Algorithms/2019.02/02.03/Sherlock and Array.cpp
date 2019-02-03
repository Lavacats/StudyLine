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

string balancedSums(vector<int> arr) {
	int totalSum = 0;
	for (int i = 0; i < arr.size(); i++) {
		totalSum += arr[i];
	}
	int leftValue = 0;
	int rightValue = totalSum;
	int answer = -1;
	for (int i = 0; i < arr.size(); i++) {
		rightValue -= arr[i];
		if (leftValue == rightValue) {
			answer = i;
			break;
		}
		leftValue += arr[i];
	}
	if (answer == -1)return "No";
	else return "Yes";
}


int main()
{

	return 0;
}
