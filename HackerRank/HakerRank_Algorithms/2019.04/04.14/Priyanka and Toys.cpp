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
int toys(vector<int> w) {
	int count = 0;
	sort(w.begin(), w.end());
	for (int i = 0; i < w.size(); i++) {
		if (w[i] != -1) {
			int value = w[i];
			for (int j = i ; j < w.size(); j++) {
				int anwer = w[j] - value;
				if (anwer <= 4 && anwer>=0) {
					w[j] = -1;
				}
			}
			count++;
		}
	}
	return count;
}
int main()
{
	vector<int> number;
	number = { 12,15,7,8,19,24 };
	toys(number);
}

