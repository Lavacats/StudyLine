// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

int equalizeArray(vector<int> arr) {
	sort(arr.begin(), arr.end());
	int maxCount = 0;
	int maxValue = 0;
	int count = 0;
	int CurNum = arr[0];
	for(int i=0; i < arr.size(); i++)
	{
		if (CurNum == arr[i])count++;
		else
		{
			if (maxCount < count)
			{
				maxCount = count;
				maxValue = arr[i-1];
			}
			CurNum = arr[i];
			count = 1;
		}
		if (i == arr.size() - 1)
		{
			if (maxCount < count)
			{
				maxCount = count;
				maxValue = arr[i-1];
			}
		}
	}
	int answer = 0;
	for (int i = 0; i < arr.size(); i++)
		if (arr[i] != maxValue)answer++;
	return answer;
}
int main()
{
	equalizeArray({ 24 ,29 ,70 ,43 ,12 ,27 ,29 ,24 ,41, 12 ,41 ,43 ,24 ,70 ,24 ,100, 41 ,43 ,43 ,100, 29, 70, 100, 43, 41, 27, 70 ,70, 59, 41, 24, 24 ,29, 43 ,24 ,27 ,70 ,24, 27, 70, 24, 70 ,27, 24, 43, 27 ,100 ,41 ,12 ,70 ,43 ,70, 62 ,12, 59, 29, 62, 41 ,100, 43, 43, 59, 59, 70, 12, 27, 43, 43, 27, 27, 27, 24, 43, 43, 62, 43, 70, 29 });
	return 0;
}

