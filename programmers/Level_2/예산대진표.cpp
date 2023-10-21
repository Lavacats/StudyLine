#include <iostream>
#include <cmath>
using namespace std;

int solution(int n, int a, int b)
{
    int answer = 0;
    int index_S=1;
    int index_E=n;
    while(true)
    {
        int center = (index_S+index_E)/2;
        if((a<=center&&b>center)||(b<=center&&a>center))
        {
            answer = log2(static_cast<int>(index_E-index_S+1));
            break;
        }
        else if(a>center)
        {
            index_S = center;
        }
        else if(a<=center)
        {
            index_E = center;
        }
        
    }

    return answer;
}
