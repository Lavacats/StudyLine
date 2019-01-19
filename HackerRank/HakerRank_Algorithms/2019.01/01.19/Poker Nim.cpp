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

int main()
{
	int q;
	cin >> q;
	while (q--)
	{
		int n, k;
		cin >> n >> k;
		int ans = 0;
		int x;
		for (int i = 0; i < n; i++)
		{
			cin >> x;
			ans ^= x;
		}
		if (ans != 0)
			cout << "First\n";
		else
			cout << "Second\n";
	}
}