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

// Complete the pangrams function below.
int theLoveLetterMystery(string s) {
	int answer = 0;
	for (int i = 0; i < s.size() / 2; i++) {
		int a = s[i];
		int b = s[s.size() - 1 - i];
		answer += abs(a - b);
	}
	return answer;
}

int main()
{

	theLoveLetterMystery("We promptly judged antique ivory buckles for the next prize");

	return 0;
}
