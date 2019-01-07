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

// Complete the minimumNumber function below.
int minimumNumber(int n, string password) {

	// case 01. 6글자 이상
	// case 02. 소문자 하나 이상 포함
	// case 03. 대문자 하나 이상 포함
	// case 04. 숫자 하나이상포함
	// case 05.!@#$%^&*()-+ 특수문자 하나이상포함
	int answer = 0;
	bool case1 = false;
	bool case2 = false;
	bool case3 = false;
	bool case4 = false;
	bool case5 = false;
	//
	//02
	for (int i = 0; i < n; i++) {
		if (password[i] >= 'a'&&password[i] <= 'z') {
			case2 = true;
			break;
		}
	}
	if (!case2)answer++;
	//03
	for (int i = 0; i < n; i++) {
		if (password[i] >= 'A'&&password[i] <= 'Z') {
			case3 = true;
			break;
		}
	}
	if (!case3)answer++;
	//04
	for (int i = 0; i < n; i++) {
		if (password[i] >= '0'&&password[i] <= '9') {
			case4 = true;
			break;
		}
	}
	if (!case4)answer++;
	//05
	for (int i = 0; i < n; i++) {
		if (password[i] == '!' ||
			password[i] == '@' ||
			password[i] == '#' ||
			password[i] == '$' ||
			password[i] == '%' ||
			password[i] == '^' ||
			password[i] == '&' ||
			password[i] == '*' ||
			password[i] == '(' ||
			password[i] == ')' ||
			password[i] == '-' ||
			password[i] == '+') {
			case5 = true;
			break;
		}
		}
	if (!case5)answer++;

	if (password.size() + answer < 6) {
		answer += (6 - (password.size() + answer));
	}
	return answer;
}

int main()
{
	minimumNumber(4,"LY!Z");

	return 0;
}
