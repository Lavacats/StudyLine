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
int chocolateFeast(int n, int c, int m) {
	int answer = 0;
	answer += n / c;
	int chocolate = n / c;		// 3
	while (true)
	{
		int freeBar = chocolate / m;	//1;
		answer += freeBar;
		chocolate -= freeBar * m;//1;
		chocolate += freeBar;//2;
		if ((freeBar + chocolate) < m)break;
	}
	return answer;
}

int main(){

	return 0;
}

