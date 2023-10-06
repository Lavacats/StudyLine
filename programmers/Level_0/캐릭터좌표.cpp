#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> keyinput, vector<int> board) {
    vector<int> answer;
    int posX=0;
    int posY=0;
    for(int i=0;i<keyinput.size();i++)
    {
        if(keyinput[i]=="up")
        {
            posY++;
        }
        if(keyinput[i]=="down")
        {
            posY--;
        }
        if(keyinput[i]=="left")
        {
            posX--;
        }
        if(keyinput[i]=="right")
        {
            posX++;
        }
        if(abs(posY)>(board[1]/2))
        {
            if(posY<0)posY++;
            else posY--;
        }
        if(abs(posX)>(board[0]/2))
        {
            if(posX<0)posX++;
            else posX--;
        }
    }
        answer.push_back(posX);
        answer.push_back(posY);
    return answer;
}
