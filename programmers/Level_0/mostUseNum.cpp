#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<int> array) {
    int answer = 0;
    int answer2=0;
    map<int,int> hackMap;
    for(int i=0;i<array.size();i++)
    {
        hackMap[array[i]]=1;
    }
    int pairNum=0;
    for(const auto& pair:hackMap)
    {
        int matchNum=0;
        for(int i=0;i<array.size();i++)
        {
            if(array[i]==pair.first)matchNum++;
        }
        if(answer<matchNum)
        {
            answer=matchNum;
            pairNum=0;
            answer2=pair.first;
        }
        else if(answer==matchNum)
        {
            pairNum=-1;
        }
        
    }
    if(pairNum==-1)
        answer2 = -1;
    
    return answer2;
}
