#include <string>
#include <vector>
#include <map>
using namespace std;

string solution(string s, string skip, int index) {
    string answer = "";
    map<char,int> skipMap;
    for(int i=0;i<skip.size();i++)skipMap[skip[i]]=1;
    
    for(int i=0; i<s.size();i++)
    {
        char chageChar;
      
        for(int j=1;j<=index;j++)
        {
            s[i]++;
            if(s[i]>'z')
            {
                s[i]-=('z'-'a'+1);
            }
            for(int k=0;k<skip.size();k++)
            {
                if(s[i]>'z')s[i]-=('z'-'a'+1);
                
                if(skipMap.find(s[i])==skipMap.end())break;
                else s[i]++;
            }
            
        }
        
        answer.push_back(s[i]);
    }
    return answer;
}
