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

int introTutorial(int V, vector<int> arr) {
	int answer = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (V == arr[i]) {
			answer = i;
		}
	}
	return answer;
}

int main(){

	return 0;
}