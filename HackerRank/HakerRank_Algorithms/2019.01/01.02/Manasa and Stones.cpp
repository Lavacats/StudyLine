// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <math.h>

using namespace std;

// Complete the stones function below.
vector<int> stones(int n, int a, int b) {
	vector<int> answer;
	int range = n - 1;
	for (int i = 0; i < n; i++) {
		int value = 0;
		if(a<b) value = (range - i)*a + i * b;
		else value = (range - i)*b + i *a;
		bool check = true;
		for (int i = 0; i < answer.size(); i++) {
			if (answer[i] == value)check = false;
		}
		if(check)answer.push_back(value);
	}
	return answer;
}

int main()
{
	stones(58,69,24);
	return 0;
}