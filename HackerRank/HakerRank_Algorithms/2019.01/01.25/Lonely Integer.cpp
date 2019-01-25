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

int lonelyinteger(vector<int> a) {
	vector<int> numbers(100);
	for (int i = 0; i < a.size(); i++) {
		numbers[a[i]]++;
	}
	int answer = 0;
	for (int i = 0; i < numbers.size(); i++) {
		if (numbers[i] == 1) {
			answer = i;
		}
	}
	return answer;
}

int main()
{
	
	return 0;
}
