#include <string>
#include <vector>

using namespace std;
int maxSum = 1000000;
void valueAccul(int num,int sum)
{
    int value1 = sum + num%10;
    int value2 = sum + (10 - num%10);
    num/=10;
    if(num==0)
    {
        if(maxSum>value1)maxSum=value1;
        if(value2<maxSum)valueAccul(num +1, value2);
    }
    else
    {
        valueAccul(num   , value1);
        valueAccul(num +1, value2);
    }
    return ;
}

int solution(int storey) {
    int answer = 0;
    valueAccul(storey, 0);
    answer = maxSum;
    return answer;
}
