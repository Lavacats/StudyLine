#include <string>
#include <vector>
#include <stack>

using namespace std;

bool isCheckString(string p)
{
    bool result=false;
    stack<char> stp;
    for(int i=0; i<p.size();i++)
    {
        if(stp.size()!=0)
        {
            if(stp.top()=='('&&p[i]==')')stp.pop();
            else stp.push(p[i]);
        }
        else stp.push(p[i]);
    }
    if(stp.size()==0)result=true;
    return result;
}

string cutString(string p)
{
    if(p=="()")return "()";
    if(p=="")return "";
    string result="";
    
    int countLeft=0;
    int countRight=0;
    string cutStringLeft="";
    string curStringRight = "";
    
    if(p[0]=='(')countLeft++;
    else if(p[0]==')')countRight++;
    cutStringLeft.push_back(p[0]);
    
    for(int i=1;i<p.size();i++)
    {
        if(p[i]=='(')countLeft++;
        else if(p[i]==')')countRight++;
        cutStringLeft.push_back(p[i]);
        if(countLeft==countRight)
        {
            curStringRight=p.substr(i+1,p.size());
            break;
        }
    }
   
    if(!isCheckString(cutStringLeft))
    {
        string cutcutString="";
        for(int i=1;i<cutStringLeft.size()-1;i++)
        {
            if(cutStringLeft[i]==')')cutcutString+='(';
            else if(cutStringLeft[i]=='(')cutcutString+=')';
        }
        result = '('+cutString(curStringRight)+')'+cutcutString;
    }
    else
    {
        result = cutStringLeft+cutString(curStringRight);
    }
    return result;
}

string solution(string p) {
    string answer = "";
    if(p.size()==0)return answer;
    answer = cutString(p);
    return answer;
}
