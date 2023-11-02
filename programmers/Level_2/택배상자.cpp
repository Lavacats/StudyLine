#include <string>
#include <vector>
#include <stack>
using namespace std;

int solution(vector<int> order) {
    int answer = 0;
    stack<int> orderStack;
    vector<int> orderVec;
    int o_index=0;
    for(int i=0; i<order.size();i++)orderVec.push_back(i+1);
    for(int i=0; i<order.size();i++)
    {
       if(orderVec[i]==order[o_index])
       {
           answer++;
           o_index++;
           while(true)
           {
               if(orderStack.empty())break;
               if(order[o_index]==orderStack.top())
               {
                   o_index++;
                   answer++;
                   orderStack.pop();
               }
               else break;
           }
       }
       else
       {
           orderStack.push(orderVec[i]);
       }
    }
    return answer;
}
