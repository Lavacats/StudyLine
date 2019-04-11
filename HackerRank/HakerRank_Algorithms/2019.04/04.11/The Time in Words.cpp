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

string NumtoString(int n) {
	string HourText = "";
	switch (n) {
	case 1:
		HourText = "one";
		break;
	case 2:
		HourText = "two";
		break;
	case 3:
		HourText = "three";
		break;
	case 4:
		HourText = "four";
		break;
	case 5:
		HourText = "five";
		break;
	case 6:
		HourText = "six";
		break;
	case 7:
		HourText = "seven";
		break;
	case 8:
		HourText = "eight";
		break;
	case 9:
		HourText = "nine";
		break;
	case 10:
		HourText = "ten";
		break;
	case 11:
		HourText = "eleven";
		break;
	case 12:
		HourText = "tweive";
		break;
	case 13:
		HourText = "thirteen";
		break;
	case 14:
		HourText = "thirteen";
		break;
	case 16:
		HourText = "sixteen";
		break;
	case 17:
		HourText = "seventeen";
		break;
	case 18:
		HourText = "eighteen";
		break;
	case 19:
		HourText = "nineteen";
		break;
	case 20:
		HourText = "twenty";
		break;
	case 21:
		HourText = "twenty one";
		break;
	case 22:
		HourText = "twenty two";
		break;
	case 23:
		HourText = "twenty three";
		break;
	case 24:
		HourText = "twenty four";
		break;
	case 25:
		HourText = "twenty five";
		break;
	case 26:
		HourText = "twenty six";
		break;
	case 27:
		HourText = "twenty seven";
		break;
	case 28:
		HourText = "twenty eight";
		break;
	case 29:
		HourText = "twenty nine";
		break;
	}
	return HourText;
}

string timeInWords(int h, int m) {

	string MinutText = "";
	string Answer = "";
	if (m == 30) {
		MinutText = "half past";
	}
	else if (m < 30) {
		if (m == 0) {
			MinutText = "o' clock";
		}
		else if (m == 15) {
			MinutText = "quarter past";
		}

	}
	else if (m > 30) {
		h++;
		if (m == 45) {
			MinutText = "quarter to";
		}
	}
	if (m == 0) {
		Answer = NumtoString(h) + " " + MinutText;
	}
	else if(m<30){
		if (m == 15) {
			Answer = MinutText + " " + NumtoString(h);
		}
		else {
			if (m == 1) {
				Answer = NumtoString(m) + " minute past " + NumtoString(h);
			}
			else {
				Answer = NumtoString(m) + " minutes past " + NumtoString(h);
			}
		}
	}
	else if (m == 30) {
		Answer = "half past " + NumtoString(h);
	}
	else if (m < 60) {
		if (m == 45) {
			Answer = MinutText + " " + NumtoString(h);
		}
		else {
			Answer = NumtoString(60 - m) + " minutes to " + NumtoString(h);
		}
	}
	return Answer;
}

int main()
{
	//ofstream fout(getenv("OUTPUT_PATH"));

	//int h;
	//cin >> h;
	///cin.ignore(numeric_limits<streamsize>::max(), '\n');

	//int m;
	//cin >> m;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string result = timeInWords(1, 1);

	//fout << result << "\n";

	//fout.close();

	return 0;
}
