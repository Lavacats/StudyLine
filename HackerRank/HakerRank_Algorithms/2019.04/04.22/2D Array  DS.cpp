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

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int inputNum = 0;
	vector<int> Element;
	cin >> inputNum;
	for (int i = 0; i < inputNum; i++) {
		int firstCode = 0;
		int secondCode = 0;
		cin >> firstCode;
		if (firstCode == 1) {
			cin >> secondCode;
			Element.push_back(secondCode);
		}
		else if (firstCode == 2) {
			Element.pop_back();
		}
		else if (firstCode == 3) {
			int maxNum = 0;
			for (int i = 0; i < Element.size(); i++) {
				if (Element[i] > maxNum) {
					maxNum = Element[i];
				}
			}
			cout << maxNum <<endl;
		}
		
	}
	return 0;
}
