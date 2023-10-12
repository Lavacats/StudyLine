#include <string>
#include <vector>

using namespace std;

int solution(int balls, int share) {
    unsigned long long answer = 1;
    int index=1;
    
    for(int i=share+1;i<=balls;i++)
    {
       if(index > balls-share) answer = answer*i;
        else
        {
            answer = answer*i/index;
            index++;
        }
    }
    return answer;
}
