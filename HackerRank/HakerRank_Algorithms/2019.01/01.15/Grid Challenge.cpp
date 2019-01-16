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

string gridChallenge(vector<string> grid) {
	for (int i = 0; i < grid.size(); i++) {
		sort(grid[i].begin(), grid[i].end());
	}
	for (int i = 0; i < grid.size(); i++) {
		if (i > 0) {
			if (grid[i][0] < grid[i - 1][grid[i].size() - 1]) {
				return "NO";
			}
		}
		for (int j = 1; j < grid[i].size(); j++) {
			if (grid[i][j - 1] >grid[i][j]) {
				return "NO";
			}
		}
	}
	return "YES";
}

int main()
{
	gridChallenge({
"kc",
"iu"

});

	return 0;
}