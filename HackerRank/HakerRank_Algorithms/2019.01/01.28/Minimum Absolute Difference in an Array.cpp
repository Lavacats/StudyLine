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

int main() {
	int t = 0;
	cin >> t;
	vector<int> answer;
	for (int i = 0; i < t; i++) {
		int num = 0;
		cin >> num;
		answer.push_back(num);
	}
	sort(answer.begin(), answer.end());
	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i];
		cout << " ";
	}

	return 0;
}