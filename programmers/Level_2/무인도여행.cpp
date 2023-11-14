#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

void SumMap(vector<string>& maps,queue<int> & queue,int y,int x)
{
    if(maps[y][x]!='X')
    {
        queue.push((maps[y][x]-'0'));
        maps[y][x]='X';
        if((x+1)<maps[y].size())SumMap(maps,queue,y,x+1);
        if(x>0)SumMap(maps,queue,y,x-1);
        if((y+1)<maps.size())SumMap(maps,queue,y+1,x);
        if(y>0)SumMap(maps,queue,y-1,x);
    }
}

int sumQueue(queue<int> queue)
{
    int result=0;
    while(true)
    {
        if(queue.empty())break;
        result+=queue.front();
        queue.pop();
    }
    return result;
}

vector<int> solution(vector<string> maps) {
    vector<int> answer;
    
    for(int i=0;i<maps.size();i++)
    {
        for(int j=0;j<maps[i].size();j++)
        {
            if(maps[i][j]!='X')
            {
                queue<int> sumQue;
                SumMap( maps,sumQue,i,j);
                answer.push_back(sumQueue(sumQue));
            }
        }
    }
    sort(answer.begin(),answer.end());
    if(answer.size()==0)answer.push_back(-1);
    return answer;
}
