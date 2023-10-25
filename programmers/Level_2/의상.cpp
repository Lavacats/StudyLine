#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    map<string,int> clothMap;
    for(int i=0;i<clothes.size();i++)
    {
        if(clothMap.find(clothes[i][1])==clothMap.end())clothMap[clothes[i][1]]=1;
    
        clothMap[clothes[i][1]]+=1;
    }
    for(const auto& pair: clothMap)
    {
        answer*=pair.second;
    }
    answer--;
    return answer;
}
