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

vector<int> missingNumbers(vector<int> arr, vector<int> brr) {
	vector<int> board(200000);
	for (int i = 0; i < brr.size(); i++) {
		board[brr[i]]++;
	}
	for (int i = 0; i < arr.size(); i++) {
		board[arr[i]]--;
	}
	vector<int> answer;
	for (int i = 0; i < board.size(); i++) {
		if (board[i] != 0)answer.push_back(i);
	}
	return answer;
}


int main()
{
	missingNumbers({ 203,204,205,206,207,208,203,205,206,204 },
		{ 203,204,204,205,206,207,205,208,203,206,205,206,204 });

	return 0;
}
