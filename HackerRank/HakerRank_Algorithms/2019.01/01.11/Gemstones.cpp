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

int gemstones(vector<string> arr) {
	for (int i = 0; i < arr.size(); i++) {
		string nonSame;
		sort(arr[i].begin(), arr[i].end());
		char curChar = arr[i][0];
		nonSame.push_back(curChar);
		for (int j = 0; j < arr[i].size(); j++) {
			if (curChar != arr[i][j]) {
				curChar = arr[i][j];
				nonSame.push_back(curChar);
			}
		}
		arr[i] = nonSame;
	}
	string curString = arr[0];
	for (int i = 1; i<arr.size(); i++) {
		
		string value;
		for (int j = 0; j < curString.size(); j++) {
			for (int k = 0; k < arr[i].size(); k++) {
				if (curString[j] == arr[i][k])value.push_back(curString[j]);
			}
		}
		curString = value;
	}
	return curString.size();
}
int main()
{
	gemstones({ 
"abcdde",
"baccd",
"eeabg" });
	return 0;
}