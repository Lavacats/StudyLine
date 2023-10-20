#include <iostream>
#include<string>
#include <stack>
using namespace std;

int solution(string s)
{
    int answer = -1;
    stack<char> mathString;

    for(int i=0;i<s.size();i++)
    {
      if(mathString.size()>0 && mathString.top() == s[i])
        {
            mathString.pop();
        }
        else
        {
            mathString.push(s[i]);
        }
    }
    if(mathString.empty()==true)
        answer = 1;
    else
        answer = 0;

    return answer;
}
