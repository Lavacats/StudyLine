#include <string>
#include <vector>
#include <queue>
using namespace std;
vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;
    int s_index=0;
    int e_inedx=0;
    int minLength=1000000;
    queue<int> numQue;
    long calSum=0;
    for(int i=0;i<sequence.size();i++)
    {
        numQue.push(sequence[i]);
        e_inedx=i;
        calSum+=sequence[i];
        
        if(calSum>k)
        {
            while(true)
            {
                int front = numQue.front();
                numQue.pop();
                calSum-=front;
                s_index++;
                if(calSum<=k)break;
            }
        }
        
        if(calSum==k)
        {
            int length = e_inedx-s_index;
            if(length<minLength)
            {
                minLength=length;
                answer.clear();
                answer.push_back(s_index);
                answer.push_back(e_inedx);
            }
        }
    }
  
    return answer;
}
