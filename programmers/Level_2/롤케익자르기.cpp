#include <string>
#include <vector>
#include <map>
using namespace std;
int solution(vector<int> topping) {
    int answer = 0;
    map<int,int> frontMap;
    map<int,int> backMap;
    for(int i=0;i<topping.size();i++)
    {
        if(frontMap.find(topping[i])==frontMap.end()) frontMap[topping[i]]=1;
        else frontMap[topping[i]]++;
    }
    for(int i=0;i<topping.size();i++)
    {
        int value = topping[topping.size()-1-i];
        if(frontMap[value]>0)
        {
            frontMap[value]--;
            if(frontMap[value]==0)frontMap.erase(value);
        }
        
        if(backMap.find(value)==backMap.end())backMap[value]=1;
        else backMap[value]++;
        
        if(frontMap.size()==backMap.size())answer++;
        
        
    }
    return answer;
}
