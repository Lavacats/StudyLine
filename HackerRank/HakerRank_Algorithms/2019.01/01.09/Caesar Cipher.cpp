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
string caesarCipher(string s, int k) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'a'&&s[i] <= 'z') {
			int a = s[i] -( 97-k);
			s[i] = (a% 26) + 97;
		}
		else if (s[i] >= 'A'&&s[i] <= 'Z') {
			int a = s[i] - (65 - k);
			s[i] = (a % 26) + 65;
		}
	}
	return s;
}

int main()
{
	caesarCipher("Ciphering.",26);
	return 0;
}