// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

// Complete the findDigits function below.
int findDigits(int n) {
	int answer = 0;
	int numN = n;
	while (true)
	{
		int value = numN % 10;
		if (value != 0 && n%value == 0)answer++;

		numN /= 10;

		if (numN < 10)
		{
			if (n%numN == 0)answer++;
			break;
		}
	}
	return answer;
}
int main()
{
	findDigits(12);

	return 0;
}
