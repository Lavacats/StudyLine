// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <list>
#include <math.h>
using namespace std;


vector<int> countingSort(vector<int> arr) {
	int maxNum = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (maxNum < arr[i])maxNum = arr[i];
	}
	vector<int> answer(maxNum+1);
	for (int i = 0; i < arr.size(); i++) {
		answer[arr[i]]++;
	}
	return answer;
}


int main()
{
	countingSort({ 1,2,99,1,1 });

	return 0;
}

