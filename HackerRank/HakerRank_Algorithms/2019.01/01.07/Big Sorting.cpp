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

// Complete the bigSorting function below.
vector<string> bigSorting(vector<string> unsorted) {
	vector<int> intSorting;
	for (int i = 0; i < unsorted.size(); i++) {
		intSorting.push_back(unsorted[i].size());
	}
	sort(intSorting.begin(), intSorting.end());
	vector<int> nonOverlap;
	int curSize = intSorting[0];
	nonOverlap.push_back(curSize);
	vector<string> answer;
	for (int i = 0; i < intSorting.size(); i++) {
		if (curSize != intSorting[i]) {
			curSize = intSorting[i];
			nonOverlap.push_back(curSize);
		}
	}
	for (int i = 0; i < nonOverlap.size(); i++) {
		vector<string> sameSizeString;
		for (int j = 0; j < unsorted.size(); j++) {
			if (nonOverlap[i] == unsorted[j].size()) {
				sameSizeString.push_back(unsorted[j]);
			}
		}
		sort(sameSizeString.begin(), sameSizeString.end());
		for (int j = 0; j < sameSizeString.size(); j++) {
			answer.push_back(sameSizeString[j]);
		}
	}
	return answer;
}

int main()
{
	bigSorting({ 
	"6",
	"31415926535897932384626433832795",
	"1",
	"3",
	"10",
	"3",
	"5"});

	return 0;
}