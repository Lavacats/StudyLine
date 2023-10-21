#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    vector<int> matchPeople;
    map<int,int> matchMap;
    
    sort(people.begin(), people.end());
    
    for(int i=0;i<people.size();i++)
    {
        if(people[i]<=(limit-people[0]))
        {
            matchPeople.push_back(people[i]);
            if(matchMap.find(people[i])!=matchMap.end())matchMap[people[i]]+=1;
            else matchMap[people[i]]=1;
        }
        else answer++;
    }
    if(matchPeople.size()>1)
    {
        int match_S=0;
        int match_E=matchPeople.size()-1;
        while(true)
        {
            if((matchPeople[match_S]+matchPeople[match_E])<=limit)
            {
                answer++;
                match_S++;
                match_E--;
            }
            else
            {
                answer++;
                match_E--;
            }
            if(match_S > match_E)break;
        }
    }
    else if(matchPeople.size()==1)answer++;
    return answer;
}
