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

string funnyString(string s) {
	string reversS;
	for (int i = s.size() - 1; i >= 0; i--)reversS.push_back(s[i]);
	vector<int> originValue;
	vector<int> reversevalue;
	for (int i = 1; i < s.size(); i++) {
		originValue.push_back(abs(s[i] - s[i - 1]));
	}
	for (int i = 1; i < reversS.size(); i++) {
		reversevalue.push_back(abs(reversS[i] - reversS[i - 1]));
	}
	for (int i = 0; i < originValue.size(); i++) {
		if (originValue[i] != reversevalue[i])return "Not Funny";
	}
	return "Funny";
}
int main()
{
	funnyString("uvzxrumuztyqyvpnji");
	return 0;
}