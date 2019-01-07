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

string Reduced(string s) {
	string answer;
	char curAlpha = s[0];
	for (int i = 0; i < s.size(); i++) {
		if (i == s.size() - 1)answer.push_back(s[i]);
		else if (s[i] == s[i + 1])i++;
		else answer.push_back(s[i]);
	}
	return answer;
}
bool ReducedCheck(string s) {
	bool answer = false;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == s[i + 1])answer = true;
	}
	return answer;
}

string superReducedString(string s) {
	if (s.size() <= 1)return "Empty String";
	while (true) {
		if (!ReducedCheck(s))break;
		s = Reduced(s);
	}
	if (s.size() == 0)return "Empty String";
	return s;
}

int main()
{
	superReducedString("aaabccddd");
	return 0;
}
