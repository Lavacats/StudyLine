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

bool is_smart_number(int num) {
	int val = (int)sqrt(num);
	if (val*val == num) {
		return true;
	}
	return false;
}

int main() {
	int test_cases;
	cin >> test_cases;
	int num;
	for (int i = 0; i < test_cases; i++) {
		cin >> num;
		bool ans = is_smart_number(num);
		if (ans) {
			cout << "YES" << endl;
		}
		else cout << "NO" << endl;
	}    
	return 0;
}


