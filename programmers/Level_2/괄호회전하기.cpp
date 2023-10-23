#include <string>
#include <vector>
#include <stack>
using namespace std;


int solution(string s) {
    int answer = 0;

    for(int i=0;i<s.size();i++)
    {
        stack<char> s_stack;
        for(int j=0;j<s.size();j++)
        {
            int index = i+j;
            if(index>=s.size())index%=(int)s.size();
            if(!s_stack.empty())
            {
                if((s_stack.top()=='(')&&(s[index]==')'))  s_stack.pop();
                else if((s_stack.top()=='{')&&(s[index]=='}'))  s_stack.pop();
                else if((s_stack.top()=='[')&&(s[index]==']'))  s_stack.pop();
                else s_stack.push(s[index]);
            }
            else s_stack.push(s[index]);
        }
        if(s_stack.empty())answer++;
    }
    return answer;
}
