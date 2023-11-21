#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void calRoad(map<int,vector<pair<int,int>>> roadMap,map<int,int>& townMap,int town,int cnt,int K)
{
    if(cnt>K )return;
    else
    {
        if(townMap.find(town)==townMap.end())townMap[town]=cnt;
        else
        {
            if(cnt<townMap[town])
            {
                townMap[town]=cnt;
            }
            else return;
        }
    }

    for(int i=0;i<roadMap[town].size();i++)
    {
        int nextTown = roadMap[town][i].first;
        int countNum = cnt + roadMap[town][i].second;
        calRoad(roadMap,townMap,nextTown,countNum,K);
    }
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 1;
    map<int,int> townMap;
    map<int,vector<pair<int,int>>> roadMap;
    
    sort(road.begin(),road.end());
    //roadMap[1].push_back(pair(1,0));
    for(int i=0;i<road.size();i++)
    {
        int minTown = min(road[i][0],road[i][1]);
        int maxTonw = max(road[i][0],road[i][1]);
        roadMap[minTown].push_back(pair(maxTonw,road[i][2]));
        roadMap[maxTonw].push_back(pair(minTown,road[i][2]));\
    }
    calRoad(roadMap,townMap,1,0,K);
    answer=townMap.size();
    return answer;
}
