#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string changeTwo(int num)
{
    string result;
    while(true)
    {
        result.push_back('0'+num%2);
        num/=2;
        if(num==0)break;
    }
   string answer;
    for(int i=(int)result.size()-1;i>=0;i--)
    {
        answer.push_back(result[i]);
    }
    return answer;
}

vector<int> solution(string s) {
    vector<int> answer;
    int changeCount=0;
    int zeroCount=0;
    while(true)
    {
        int m_length=0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]!='0')m_length++;
            else zeroCount++;
        }
        s = changeTwo(m_length);
        changeCount++;
        if(s=="1")break;
    }
    answer.push_back(changeCount);
    answer.push_back(zeroCount);
    return answer;
}
