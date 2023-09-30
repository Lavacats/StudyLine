#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    int answer = 0;
    float num_Fa = (float)a;
    float num_Fb = (float)b;
    float num_Value = num_Fa/num_Fb;
    int num_Gb=b;
    
    while(true)
    {
        if(num_Gb%2==0)num_Gb/=2;
        else if(num_Gb%5==0)num_Gb/=5;
        else break;
    }
   
    if(a%num_Gb==0)
    {
       answer=1;
    }
    else
    {
        answer=2;
    }
    return answer;
}
