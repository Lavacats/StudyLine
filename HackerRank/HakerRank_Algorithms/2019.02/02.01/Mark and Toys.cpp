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

int maximumToys(vector<int> prices, int k) {
	sort(prices.begin(), prices.end());
	int count = 0;
	int answer = 0;
	for (int i = 0; i < prices.size(); i++) {
		if (k >= prices[i]) {
			if (count + prices[i] <= k) {
				answer++;
				count += prices[i];
			}
			else{
				break;
			}
		}
		else {
			break;
		}
	}
	return answer;
}
int main()
{
	maximumToys({ 1,2,3,4 }, 7);
	return 0;
}
