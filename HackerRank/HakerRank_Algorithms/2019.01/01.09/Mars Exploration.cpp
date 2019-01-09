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

int marsExploration(string s) {
	int count = 0;
	for (int i = 0; i < s.size(); i++) {
		if (i % 3 == 0) {
			if (s[i] != 'S')count++;
		}
		else if (i % 3 == 1) {
			if (s[i] != 'O')count++;
		}
		else if (i % 3 == 2) {
			if (s[i] != 'S')count++;
		}
	}
	return count;
}

int main()
{
	caesarCipher("Ciphering.",26);
	return 0;
}