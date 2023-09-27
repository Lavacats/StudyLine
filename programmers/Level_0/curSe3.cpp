
#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    for(int i=1;i<=n;i++)
    {
        
        answer++;
        
        if((answer%3==0)||(answer%10==3))
        {
            while(true)
            {
                answer++;
             
                if((answer%3!=0)&&(answer%10)!=3&&(answer<30||answer>39)&&(answer<130||answer>139))break;}
        }
        
    }
    return answer;
}
