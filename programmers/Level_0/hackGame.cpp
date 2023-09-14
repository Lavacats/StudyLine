#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board) {
    int answer = 0;
    size_t hor = board.size();
    size_t ver = board[0].size();
    
    for(int i=0; i<hor;i++)
    {
        for(int k=0;k<ver;k++)
        {
            int count=0;
            if(board[i][k]==0)
            {
                if(i>0)
                {
                    if(board[i-1][k]==1)count++;
                }
                if(i<hor-1)
                {
                    if(board[i+1][k]==1)count++;
                }
                if(k>0)
                {
                    if(board[i][k-1]==1)count++;
                }
                if(k<ver-1)
                {
                    if(board[i][k+1]==1)count++;
                }
                if(i>0&&k>0)
                {
                    if(board[i-1][k-1]==1)count++;
                }
                if(i<hor-1&&k>0)
                {
                    if(board[i+1][k-1]==1)count++;
                }
                 if(i>0&&k<ver-1)
                {
                    if(board[i-1][k+1]==1)count++;
                }
                if(i<hor-1&&k<ver-1)
                {
                    if(board[i+1][k+1]==1)count++;
                }
            }
            if(count==0 && board[i][k]!=1)answer++;
        }
    }
    
    return answer;
}
