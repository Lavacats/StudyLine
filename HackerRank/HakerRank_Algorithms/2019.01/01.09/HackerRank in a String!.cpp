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

string hackerrankInString(string s) {
	string find = "hackerrank";
	int stringCount = 0;
	for (int i = 0; i < s.size(); i++) {
		if (find[stringCount] == s[i]) {
			stringCount++;
		}
	}
	if(stringCount == find.size())return "YES";
	else "NO";
}


int main()
{
	hackerrankInString("hackerrank.");
	return 0;
}