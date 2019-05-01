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


stirng shortStr(string str) {
	int strSzie = str.size();
	string shortStr;
	char curChar = str[0];
	int charCount = 0;
	for (int i = 0; i < str.size(); i++) {
		if (curChar == str[i]) {
			charCount++;
		}
		else {
			shortStr.push_back(curChar);
			shortStr.push_back(charCount);
		}
	}
}
