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
	int vectorsize = 0;
	int rotateCount = 0;
	cin >> vectorsize;
	cin >> rotateCount;
	vector<int> rotateVector;
	for (int i = 0; i < vectorsize; i++) {
		int inputNum;
		cin >> inputNum;
		rotateVector.push_back(inputNum);
	}
	for (int i = 0; i < vectorsize; i++) {
		std::cout << rotateVector[(rotateCount + i) % vectorsize] << " ";
	}
}
