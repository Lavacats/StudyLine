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
	sort(arr.begin(), arr.end());
	return arr;

}
int main()
{
	countingSort({ 1,2,99,1,1 });

	return 0;
}

