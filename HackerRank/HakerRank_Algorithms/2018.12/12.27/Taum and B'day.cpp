// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

vector<string> split_string(string);

// Complete the taumBday function below.
unsigned long long taumBday(unsigned long long b, unsigned long long w, unsigned long long bc, unsigned long long wc, unsigned long long z) {
	unsigned long long answer = 0;
	unsigned long long blackCount = 0;
	unsigned long long whiteCount = 0;

	
	blackCount = b * (min(bc, wc + z));
	int msf = blackCount / b;
	whiteCount = w * (min(wc, bc + z));
	answer = blackCount + whiteCount;
	return answer;
}

int main()
{
	taumBday(27984 ,1402
		,619246 ,615589, 247954);
	return 0;
}
