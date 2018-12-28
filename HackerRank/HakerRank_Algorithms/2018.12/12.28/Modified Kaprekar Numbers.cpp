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

// Complete the kaprekarNumbers function below.

int sumNumber(long long num)
{
	int copyNum = num;
	int countNum = 0;
	while (true)
	{
		copyNum /= 10;
		countNum++;
		if (copyNum == 0)break;
	}
	
	int copyNum2 = num;
	int frontNum = 0;
	int backNum = 0;
	for (int i = 0; i < countNum-(countNum / 2); i++)copyNum2 /= 10;
	frontNum = copyNum2;
	for (int i = 0; i < countNum - (countNum / 2); i++)copyNum2 *= 10;
	backNum = num - copyNum2;

	return frontNum + backNum;
}

void kaprekarNumbers(int p, int q) {
	int count = 0;
	for (int i = p; i <= q; i++)
	{
		if (i == sumNumber((long long)pow(i, 2)))
		{
			cout << i << " ";
			count++;
		}
	}
	if (count == 0)cout << "INVALID RANGE";
}

int main()
{
	int p;
	cin >> p;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int q;
	cin >> q;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	kaprekarNumbers(p, q);

	return 0;
}
