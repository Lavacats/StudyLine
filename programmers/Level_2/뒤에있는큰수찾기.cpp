#include <string>
#include <vector>
#include <map>
#include <utility>
#include <stack>
using namespace std;
vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    stack<pair<int,int>> numberStack;
    for(int i=0;i<numbers.size();i++)answer.push_back(-1);
    for(int i=0;i<numbers.size();i++)
    {
        if(!numberStack.empty())
        {
            if(numberStack.top().first<numbers[i])
            {
                int index=i-1;
                while(true)
                {
                    int numIndex = numberStack.top().second;
                    answer[numIndex] = numbers[i];
                    numberStack.pop();
                    if(numberStack.empty())break;
                    else
                    {
                        if(numberStack.top().first>=numbers[i])break;
                    }
                }
            }
        }
        numberStack.push(pair(numbers[i],i));
        
    }
    return answer;
}
