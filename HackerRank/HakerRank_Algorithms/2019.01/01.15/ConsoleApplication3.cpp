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

bool findPalindrome(string s) {
	bool answer = true;
	for (int i = 0; i < s.size() / 2; i++) {
		if (s[i] != s[s.size() - 1 - i]) {
			answer = false;
			break;
		}
	}
	return answer;
}

int palindromeIndex(string s) {
	if (findPalindrome(s))return -1;
	int answer = -1;
	for (int i = 0; i < s.size() / 2; i++) {
		if (s[i] != s[s.size() - 1 - i]) {
			string dummy;
			for (int j = 0; j < s.size(); j++) {
				if (j != i)dummy.push_back(s[j]);
			}
			if (palindromeIndex(dummy)) {
				answer = i;
			}
			else {
				for (int j = 0; j < s.size(); j++) {
					if (j != (s.size() - 1 - i))dummy.push_back(s[j]);
				}
				if (palindromeIndex(dummy))answer = s.size() - 1 - i;
			}
		}
	}
	return answer;
}

int main()
{
	palindromeIndex("aaab");

	return 0;
}
