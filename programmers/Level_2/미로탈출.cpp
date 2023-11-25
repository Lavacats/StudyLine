#include <string>
#include <vector>
#include <queue>
using namespace std;

int carLength(vector<vector<int>> maps,pair<int,int> start,pair<int,int> end)
{
    queue<pair<int,int>> mapQue;
    mapQue.push(start);
    
    while (!mapQue.empty())
    {
        pair<int,int> current = mapQue.front();
        mapQue.pop();
        
        int currentY = current.first;
        int currentX = current.second;
        
        if(currentY==end.first&&currentX==end.second)break;
        
        if(currentX>0)
        {
            if(maps[currentY][currentX-1]==0)
            {
                mapQue.push(pair(currentY,currentX-1));
                maps[currentY][currentX-1]=maps[currentY][currentX]+1;
            }
        }
        if(currentY>0)
        {
            if(maps[currentY-1][currentX]==0)
            {
                mapQue.push(pair(currentY-1,currentX));
                maps[currentY-1][currentX]=maps[currentY][currentX]+1;
            }
        }
        if(currentX<maps[0].size()-1)
        {
            if(maps[currentY][currentX+1]==0)
            {
                mapQue.push(pair(currentY,currentX+1));
                maps[currentY][currentX+1]=maps[currentY][currentX]+1;
            }
        }
        if(currentY<maps.size()-1)
        {
            if( maps[currentY+1][currentX]==0)
            {
                mapQue.push(pair(currentY+1,currentX));
                maps[currentY+1][currentX]=maps[currentY][currentX]+1;
            }
        }
    }
    return maps[end.first][end.second];
}

int solution(vector<string> maps)
{
    pair<int,int> startIndex;
    pair<int,int> buttonIndex;
    pair<int,int> goalIndex;
    vector<vector<int>> numMap;
    for(int i=0;i<maps.size();i++)
    {
        vector<int> numVec;
        for(int j=0;j<maps[i].size();j++)
        {
            if(maps[i][j]=='S')startIndex   = pair(i,j);
            if(maps[i][j]=='L')buttonIndex  = pair(i,j);
            if(maps[i][j]=='E')goalIndex    = pair(i,j);
            
            if(maps[i][j]!='X')numVec.push_back(0);
            else numVec.push_back(-1);
        }
        numMap.push_back(numVec);
    }
    int sTob = carLength(numMap,startIndex,buttonIndex);
    int bToE = carLength(numMap,buttonIndex,goalIndex);
    if(sTob==0||bToE==0)return -1;
    return sTob+bToE;
}
