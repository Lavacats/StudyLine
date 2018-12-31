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

// Complete the workbook function below.
int workbook(int n, int k, vector<int> arr) {
	int maxNum = 0;
	for (int i = 0; i < arr.size(); i++){
		if (arr[i] % k == 0)maxNum += arr[i] / k;
		else maxNum += arr[i] / k + 1;
	}
	vector<vector<int>> page(maxNum);
	int addNum = 0;
	for (int i = 0; i <n; i++){
		int curArr = arr[i];
		for (int j = 0; j <curArr; j++){
			page[(j / k)+ addNum].push_back(j+1);
		}
		if (curArr%k==0)addNum += curArr / k;
		else addNum+=(curArr / k) + 1;
	}
	int answer = 0;
	for (int i = 0; i < page.size(); i++) {
		for (int j = 0; j < page[i].size(); j++) {
			if ((i+1) == page[i][j])
			{
				answer++;
				break;
			}
		}
	}
	return answer;
}

int main()
{
	workbook(15, 20, { 1, 8 ,19 ,15, 2 ,29, 3 ,2 ,25, 2, 19 ,26, 17 ,33 ,22 });

	return 0;
}

