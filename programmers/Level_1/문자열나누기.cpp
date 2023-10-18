#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int answer = 0;
    for(int i=0;i<s.size();i++)
    {
        char matchChar = s[i];
        int matchNum=1;
        int unMatch=0;
        bool isCheck=false;
        for(int j=i+1;j<s.size();j++)
        {
            if(matchChar==s[j])matchNum++;
            else unMatch++;
            
            i++;
            if(matchNum==unMatch)
            {
                isCheck=true;
                answer++;
                break;
            }
        }
         if(i>=((int)s.size()-2) && isCheck==false)
        {
            answer++;
        }
    }
    
    return answer;
}
