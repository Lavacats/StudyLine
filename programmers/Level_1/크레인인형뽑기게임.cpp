#include <string>
#include <vector>

using namespace std;


int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    vector<int> vecAnswer;
    for(int i=0;i<moves.size();i++)
    {
        int pushNum=0;
        for(int j=0;j<board.size();j++)
        {
            if(board[j][moves[i]-1]!=0)
            {
                pushNum=board[j][moves[i]-1];
                board[j][moves[i]-1]= 0;
                break;
            }
        }
        if(pushNum!=0)vecAnswer.push_back(pushNum);
        if(vecAnswer.size()>=2)
        {
            while(true)
            {
                bool isCheck=true;
                int prevNum=vecAnswer[0];
                for(int k=1;k<vecAnswer.size();k++)
                {
                    if(vecAnswer[k]==prevNum)
                    {
                        vecAnswer.erase(vecAnswer.begin() + k);
                        vecAnswer.erase(vecAnswer.begin() + k-1);
                        isCheck=false;
                        answer+=2;
                        break;
                    }
                    prevNum = vecAnswer[k];
                }
                if(isCheck)break;
                if(vecAnswer.size()<2)break;
            }
        }
        
    }
    return answer;
}
