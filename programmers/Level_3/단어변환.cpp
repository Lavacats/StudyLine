#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int isCheckString(string st_1,string st_2)
{
    int result=0;
    int checkCount=0;
    for(int i=0;i<st_1.size();i++)if(st_1[i]!=st_2[i])checkCount++;
    if(checkCount>1)result=2;
    else if(checkCount==1)result=1;
    else if(checkCount==0)result=0;
    return result;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    bool isCheck=true;
    queue<string> stque;
    map<string,string> mapWord;
    
    stque.push(begin);
    mapWord[begin];
    for(int i=0;i<words.size();i++)mapWord[words[i]];
   
    if(mapWord.find(target)==mapWord.end())return 0;
    while(isCheck)
    {
        string popSt = stque.front();
        int count=0;
        vector<string> vecWords;
        stque.pop();
        
        for(int i=0;i<words.size();i++)
        {
            if(isCheckString(popSt, words[i])==1)
            {
                count++;
                if(words[i]==target)
                {
                    isCheck=false;
                    mapWord[words[i]] =(popSt);
                    break;
                }
                stque.push(words[i]);
                mapWord[words[i]] =(popSt);
            }
            else vecWords.push_back(words[i]);
        }
        words = vecWords;
        if(count==0)isCheck=false;
    }
    if(mapWord[target].size()==0)return 0;
    else
    {
        string preSt = mapWord[target];
        while(true)
        {
            answer++;
            if(preSt==begin)break;
            preSt = mapWord[preSt];
        }
    }
    return answer;
}
