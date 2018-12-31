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


vector<string> split_string(string);
vector<int> serviceLane(int n, vector<vector<int>> cases, vector<int> width) {
	vector<int> answer;
	for (int i = 0; i < cases.size(); i++)
	{
		int firstNum = cases[i][0];
		int secondNum = cases[i][1];
		int minNum = 100000;
		for (int j = firstNum; j <= secondNum; j++)
		{
			if (width[j] < minNum)minNum = width[j];
		}
		answer.push_back(minNum);
	}
	return answer;
}

int main(){

	return 0;
}

