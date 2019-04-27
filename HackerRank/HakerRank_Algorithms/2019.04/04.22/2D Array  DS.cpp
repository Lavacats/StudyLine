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

int Function_1(string str, string chageStr) {
	int answer = abs(str.length - chageStr.length);
	return answer;
}

int Function_2(string str, string chageStr) {
	sort(str.begin(), str.end());
	sort(chageStr.begin(), chageStr.end());
	int num = 0;
	
}

void Function(string str, string chageStr) {
	int try1 = Function_1(str, chageStr);
}