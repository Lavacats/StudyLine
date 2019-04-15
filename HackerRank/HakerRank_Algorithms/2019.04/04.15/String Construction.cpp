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

int stringConstruction(string s) {
	sort(s.begin(), s.end());
	char curChar = s[0];
	int count = 1;
	for (int i = 0; i < s.size(); i++) {
		if (curChar != s[i]) {
			count++;
			curChar = s[i];
		}
	}
	return count;
}


int main()
{

	stringConstruction("aabb");

	return 0;
}

