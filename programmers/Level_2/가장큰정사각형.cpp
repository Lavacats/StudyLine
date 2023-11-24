#include <iostream>
#include<vector>
#include <vector>
#include <algorithm>
using namespace std;
int solution(vector<vector<int>> board)
{
    int answer =board[0][0];
    for(int i=1; i<board.size();i++)
    {
        for(int j=1;j<board[i].size();j++)
        {
            if(board[i][j]==1)
            {
                board[i][j]=1+min({board[i][j-1],board[i-1][j],board[i-1][j-1]});
                answer = max(board[i][j],answer);
            }
        }
    }
    return answer*answer;
}
