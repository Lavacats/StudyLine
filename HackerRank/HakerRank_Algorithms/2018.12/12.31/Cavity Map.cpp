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
vector<string> cavityMap(vector<string> grid) {
	vector<string> dummy;
	for (int i = 0; i < grid.size(); i++) dummy.push_back(grid[i]);
	for (int i = 1; i < dummy.size() - 1; i++) {
		for (int j = 1; j < dummy[i].size() - 1; j++) {
			bool check = true;
			if (dummy[i][j] <=dummy[i + 1][j])check = false;
			if (dummy[i][j] <=dummy[i - 1][j])check = false;
			if (dummy[i][j] <=dummy[i][j + 1])check = false;
			if (dummy[i][j] <=dummy[i][j - 1])check = false;
			if (check == true)grid[i][j] = 'X';
		}
	}
	return grid;
}

int main()
{

	cavityMap(
	{	"1112",
		"1912",
		"1892",
		"1234"
	});
	return 0;
}
