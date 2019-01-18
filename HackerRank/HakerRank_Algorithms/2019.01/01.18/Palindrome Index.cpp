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

bool findPalindrome(string str) {
	bool answer = true;
	for (int i = 0; i < str.size() / 2; i++) {
		if (str[i] != str[str.size() - 1 - i]) {
			answer = false;
			break;
		}
	}
	return answer;
}

int palindromeIndex(string s) {
	int firstNum = 0;
	int lastNum = 0;
	for (int i = 0; i < s.size() / 2; i++) {
		if (s[i] != s[s.size() - 1 - i]) {
			firstNum = i;
			lastNum = s.size() - 1 - i;
			break;
		}
	}
	string firstDel;
	for (int i = 0; i < s.size() / 2; i++) {
		if (i != firstNum)firstDel.push_back(s[i]);
	}
	if (findPalindrome(firstDel))return firstNum;
	string secondDel;
	for (int i = 0; i < s.size() / 2; i++) {
		if (i != lastNum)secondDel.push_back(s[i]);
	}
	if (findPalindrome(secondDel))return lastNum;
	return -1;
}
int main()
{
	palindromeIndex("aaab");

	return 0;
}