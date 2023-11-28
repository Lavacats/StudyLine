#include <string>
#include <vector>
#include <cmath>
using namespace std;

long long solution(int k, int d)
{
    long long answer = 0;
    long long maxLength = pow(d,2);
    
    for(long long i=0;i<=d;i+=k)
    {
        // i 가 Y
        int m_X = sqrt(maxLength-i*i);
        answer+=m_X/k+1;
    }
    return answer;
}
