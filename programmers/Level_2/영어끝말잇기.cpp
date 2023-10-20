#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;


vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    char preChar = words[0][0];
    int roofTime=1;
    map<string,int> worldMap;
    for(int i=0;i<words.size();i++)
    {
        int index=i%n;
        index++;
        if(words[i][0]==preChar)
        {
            if(worldMap.find(words[i])==worldMap.end())
            {
                preChar = words[i][words[i].size()-1];
                worldMap[words[i]]=index;
            }
            else
            {
                answer.push_back(index);
                answer.push_back(roofTime);
                break;
            }
        }
        else
        {
            answer.push_back(index);
            answer.push_back(roofTime);
            break;
        }
        if((i+1)%n==0)roofTime++;
    }
    if(answer.size()==0)
    {
        answer.push_back(0);
          answer.push_back(0);
    }
    return answer;
}
