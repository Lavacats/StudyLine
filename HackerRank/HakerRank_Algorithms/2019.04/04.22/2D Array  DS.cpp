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

int hourglassSum(vector<vector<int>> arr) {
	int answer = -100;
	// 배열값은 -9보다 작을 수 없고, 따라서 모래시계 모양의 합은 -63 보다 작을 수없다
	for (int i = 0; i < arr.size() - 2; i++) {
		for (int j = 0; j < arr[i].size() - 2; j++) {
			int arrSumValue = 0;
			arrSumValue += arr[i][j] + arr[i][j + 1] + arr[i][j + 2];
			arrSumValue += arr[i + 1][j + 1];
			arrSumValue += arr[i + 2][j] + arr[i + 2][j + 1] + arr[i + 2][j + 2];
			// 모래시계 모양의 값의 합
			if (answer < arrSumValue) {
				answer = arrSumValue;
				// answer은 처음에 최소값을 가지며, 큰 값이 나올 때마다 값을 교체합니다.
			}
		}
	}
	return answer;
}
