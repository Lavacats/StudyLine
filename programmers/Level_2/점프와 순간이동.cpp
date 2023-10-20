#include <iostream>
using namespace std;

int solution(int n)
{
    int ans = 0;
    
    while(true)
    {
        if(n==1)
        {
            ans++;
            break;
        }
        else if(n%2!=0)
        {
            ans++;
        }
        n/=2;
    }
    
    return ans;
}
