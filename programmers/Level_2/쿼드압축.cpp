#include <string>
#include <vector>

using namespace std;


vector<vector<int>> MAP;

void countNumArr(int startX,int startY,int size,vector<int>& answer)
{
    bool numOne=true;
    bool numZero=true;
    for(int i=startY;i<startY+size;i++)
    {
        for(int j=startX;j<startX+size;j++)
        {
            if(MAP[i][j]==1)numZero=false;
            if(MAP[i][j]==0)numOne=false;
        }
    }
   if(numZero)
   {
       answer[0]++;
       return;
   }
    if(numOne)
    {
        answer[1]++;
        return;
    }
    size /=2;
    countNumArr(startX+size,startY+size,size,answer);
    countNumArr(startX,     startY+size,size,answer);
    countNumArr(startX+size,startY,size,answer);
    countNumArr(startX,     startY,size,answer);
}

vector<int> solution(vector<vector<int>> arr) {
    vector<int> answer(2,0);
     MAP = arr;
    countNumArr(0, 0, arr.size(), answer);
    return answer;
}
