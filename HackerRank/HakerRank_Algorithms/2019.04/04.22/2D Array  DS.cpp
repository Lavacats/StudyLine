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

vector<int> reverseArray(vector<int> a) {
	vector<int> answer;
	for (int i = 0; i < a.size(); i++) {
		answer.push_back(a[a.size() - i-1]);
	}
	return answer;
}
