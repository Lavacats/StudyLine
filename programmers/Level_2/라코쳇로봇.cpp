#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int solution(vector<string> board)
{
    int answer = 0;
    pair<int,int> curPos;
    pair<int,int> goal;
    queue<pair<int,int>> searchQue;
    map<pair<int,int>,int> searchMap;
    for(int i=0;i<board.size();i++)
    {
        for(int j=0;j<board[i].size();j++)
        {
            if(board[i][j]=='R')
            {
                curPos = pair(i,j);
                board[i][j]='.';
                searchQue.push(curPos);
                searchMap[curPos]=0;
            }
            if(board[i][j]=='G')
            {
                goal = pair(i,j);
                board[i][j]='.';
            }
        }
    }
    while(true)
    {
        if(searchQue.empty())break;
        pair<int,int> curRot = searchQue.front();
        int countMap = searchMap[curRot]+1;
        searchQue.pop();
        
        int upArrow=curRot.first;
        int downArrow=curRot.first;
        int leftArrow=curRot.second;
        int rightArrow=curRot.second;
        
        for(int i=1;i<=curRot.first;i++)
        {
            if(board[curRot.first-i][curRot.second]=='.')upArrow--;
            else if(board[curRot.first-i][curRot.second]=='D')break;
        }
        if(upArrow!=curRot.first)
        {
            if(searchMap.find(pair(upArrow,curRot.second))==searchMap.end())
            {
                searchQue.push(pair(upArrow,curRot.second));
                searchMap[pair(upArrow,curRot.second)]=countMap;
            }
        }
        if(goal==pair(upArrow,curRot.second))break;
        
        for(int i=curRot.first+1;i<board.size();i++)
        {
            if(board[i][curRot.second]=='.')downArrow++;
            else if(board[i][curRot.second]=='D')break;
        }
        if(downArrow!=curRot.first)
        {
            if(searchMap.find(pair(downArrow,curRot.second))==searchMap.end())
            {
                searchQue.push(pair(downArrow,curRot.second));
                searchMap[pair(downArrow,curRot.second)]=countMap;
            }
        }
        if(goal==pair(downArrow,curRot.second))break;
            
        for(int i=1;i<=curRot.second;i++)
        {
            if(board[curRot.first][curRot.second-i]=='.')leftArrow--;
            else if(board[curRot.first][curRot.second-i]=='D')break;
        }
        if(leftArrow!=curRot.second)
        {
            if(searchMap.find(pair(curRot.first,leftArrow))==searchMap.end())
            {
                searchQue.push(pair(curRot.first,leftArrow));
                searchMap[pair(curRot.first,leftArrow)]=countMap;
            }
        }
        if(goal==pair(curRot.first,leftArrow))break;
        
        for(int i=curRot.second+1;i<board[0].size();i++)
        {
            if(board[curRot.first][i]=='.')rightArrow++;
            else if(board[curRot.first][i]=='D')break;
        }
        if(rightArrow!=curRot.second)
        {
            if(searchMap.find(pair(curRot.first,rightArrow))==searchMap.end())
            {
                searchQue.push(pair(curRot.first,rightArrow));
                searchMap[pair(curRot.first,rightArrow)]=countMap;
            }
        }
        if(goal==pair(curRot.first,leftArrow))break;
    }
    if(searchMap.find(goal)!=searchMap.end())answer = searchMap[goal];
    else answer=-1;
    return answer;
}
