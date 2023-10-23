#include <string>
#include <vector>
#include <map>
#include <functional> 
using namespace std;

int solution(int k, vector<int> tangerine) {
    int answer = 0;
    map <int,int> boxMap;
    for(int i=0; i<tangerine.size();i++)
    {
        if(boxMap.find(tangerine[i])==boxMap.end())boxMap[tangerine[i]]=1;
        else boxMap[tangerine[i]]+=1;
    }
    vector<int> boxVec;
    for (const auto& pair : boxMap)boxVec.push_back(pair.second);
    
    sort(boxVec.begin(),boxVec.end(), std::greater<int>());
   
    int boxCount=0;
    for(int i=0; i<boxVec.size();i++)
    {
        boxCount+=boxVec[i];
        answer++;
        if(boxCount>=k)
        {
            break;
        }
        
    }
    return answer;
}
