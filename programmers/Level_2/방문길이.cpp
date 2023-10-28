#include <string>
#include <map>
#include <utility>
#include <vector>
using namespace std;

int solution(string dirs) {
    int answer = 0;
    vector<vector<int>> dirMap;
    map<pair<int,int>,int> lengthMap;
    int index=0;
    int startPosX = 5;
    int startPosY = 5;

    for(int i=0;i<11;i++)
    {
        vector<int> lengthVec;
        for(int j=0;j<11;j++)
        {
            lengthVec.push_back(index);
            index++;
        }
        dirMap.push_back(lengthVec);
    }
    int startPos = dirMap[startPosY][startPosX];
    for(int i=0;i<dirs.size();i++)
    {
        int prevPos = dirMap[startPosY][startPosX];
        if(dirs[i]=='U')
        {
            if((startPosY-1)>=0)startPosY--;
        }
        else if(dirs[i]=='D')
        {
            if((startPosY+1)<11)startPosY++;
        }
        else if(dirs[i]=='R')
        {
            if((startPosX+1)<11)startPosX++;
        }
        else if(dirs[i]=='L')
        {
            if((startPosX-1)>=0)startPosX--;
        }
        int curPos = dirMap[startPosY][startPosX];
        if(prevPos!=curPos)
        {
            int key = min(prevPos,curPos);
            int value = max(prevPos,curPos);
            if(lengthMap.find(pair(key,value))==lengthMap.end())
            {
                lengthMap[pair(key,value)] = 1;
                answer++;
            }
        }
    }
    return answer;
}
