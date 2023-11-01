#include <string>
#include <vector>

using namespace std;

int MAXvalue = 10000001;
int checkNum[1000001] = { 0, };

int calcaraiton(int x, int y,int n, int length)
{
    if(checkNum[x] != 0 && checkNum[x] <= length)return MAXvalue;
    
    checkNum[x] = length;
    
    if(x == y) return length;
    
    int plusN = MAXvalue;
    int mul2 = MAXvalue;
    int mul3 = MAXvalue;
    if(x + n <= y)
        plusN = calcaraiton(x + n, y, n, length + 1);
    
    if(x * 2 <= y)
        mul2 = calcaraiton(x * 2, y, n, length + 1);
    
    if(x * 3 <= y)
        mul3 = calcaraiton(x * 3, y, n, length + 1);
    
    return min(plusN, min(mul2, mul3));
}

int solution(int x, int y, int n) {
    int answer = 0;
    answer = calcaraiton(x,y,n,0);
    if(answer>=1000000)answer=-1;
    return answer;
}
