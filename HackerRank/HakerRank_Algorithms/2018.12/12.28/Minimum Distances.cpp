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


int minimumDistances(vector<int> a) {
	vector<int> oneTub;
	for (int i = 0; i < a.size(); i++)oneTub.push_back(a[i]);
	sort(oneTub.begin(), oneTub.end());

	vector<int> sameNum;
	int curNum = oneTub[0];
	int curCount = 1;
	for (int i = 0; i < oneTub.size()-1; i++)
	{
		if (oneTub[i] != oneTub[i + 1])
		{
			if (curCount > 1)
			{
				sameNum.push_back(curNum);
				curCount = 1;
			}
		}
		else
		{
			curCount++;
			curNum = oneTub[i];
		}
		if (i == oneTub.size() - 2 && (curCount > 1))
		{
			sameNum.push_back(curNum);
		}
	}
	if (sameNum.size() == 0)return -1;
	int minDistance = a.size() - 1;
	for (int i = 0; i < sameNum.size(); i++)
	{
		int distance = a.size();
		int first = -1;
		int last = -1;
		for (int j= 0; j < a.size(); j++)
		{
			if (sameNum[i] == a[j] && first == -1)first = j;
			else if (first != -1 &&last==-1&& sameNum[i] == a[j])
			{
				last = j;
				if (distance > (last - first))
				{
					distance = last - first;
					first = last;
					last = -1;
				}
			}
		}
		if (distance < minDistance)
		{
			minDistance = distance;
		}
	}
	return minDistance;
}

int main()
{
	minimumDistances({ 1,2,3,4,10 });

	return 0;
}
