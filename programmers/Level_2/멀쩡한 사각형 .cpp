
#include <string>
#include <vector>
#include <bitset>
using namespace std;

int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long solution(int w,int h)
{
    long long answer = (long long)w * (long long)h - (w+h);

    answer +=calculateGCD(w,h);
    return answer;
}
