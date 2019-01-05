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

// Complete the strangeCounter function below.
long strangeCounter(long t) {
	long index = 3;
	long count = 1;
	while (true) {
		if (t <= index)break;
		count++;
		index += 3 * (pow(2,count-1));
	}
	long answer = 0;
	long value = 3 * (pow(2, count - 1));
	long startNum = index - (value - 1);
	long lastNum = index;
	t -= startNum;
	answer = value - t;
	return answer;
}

int main()
{
	strangeCounter(17);
	return 0;
}
