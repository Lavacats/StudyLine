#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    map<int,int> anMap;
    vector<vector<int>> numVector;
    vector<int> numCount;
    int numValue=0;
    for(int i=1;i<s.size()-1;i++)
    {
        if(s[i]=='{'){}
        else if(s[i]=='}')
        {
            i+=2;
            numCount.push_back(numValue);
            numVector.push_back(numCount);
            numCount.clear();
            numValue=0;
        }
        else
        {
            if(s[i]==',')
            {
                numCount.push_back(numValue);
                numValue=0;
            }
            else if(s[i]>='0'&&s[i]<='9')
            {
                numValue*=10;
                numValue+=(s[i]-'0');
            }
        }
    }
    while(true)
    {
        int minSize=1000000;
        int index=-1;
        for(int i=0;i<numVector.size();i++)
        {
            if(numVector[i].size()<minSize)
            {
                minSize = (int)numVector[i].size();
                index=i;
            }
        }
        for(int i=0;i<numVector[index].size();i++)
        {
            if(anMap.find(numVector[index][i])==anMap.end())
            {
                answer.push_back(numVector[index][i]);
                anMap[numVector[index][i]]=1;
            }
        }
        numVector.erase(numVector.begin() + index);
        if(numVector.size()<=0)break;
    }
    return answer;
}
