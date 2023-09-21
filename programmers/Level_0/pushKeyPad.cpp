#include <string>
#include <vector>

using namespace std;

int NumLength(int cur, int push)
{
    vector<vector<int>> phonePad = {{1,2,3},{4,5,6},{7,8,9},{-1,0,-1}};
    
    int curX = -1;
    int curY = -1;
    int pushX = -1;
    int pushY = -1;
    for(int i=0;i<phonePad.size();i++)
    {
        for(int j=0;j<phonePad[i].size();j++)
        {
            if(phonePad[i][j]==cur)
            {
                curX = j;
                curY = i;
            }
            if(phonePad[i][j]==push)
            {
                pushX = j;
                pushY = i;
            }
        }
    }
    int solution = abs(curX-pushX)+abs(curY-pushY);
    return solution;
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int num_R = -1;
    int num_L = -1;
    for(int i=0;i<numbers.size();i++)
    {
        if(numbers[i]==1 || numbers[i]==4||numbers[i]==7)
        {
            answer+="L";
            num_L = numbers[i];
        }
        else if(numbers[i]==3 || numbers[i]==6||numbers[i]==9)
        {
            answer+="R";
            num_R = numbers[i];
        }
        else 
        {
            int length_R = NumLength(num_R,numbers[i]);
            int length_L = NumLength(num_L,numbers[i]);
            
            if(length_R>length_L)
            {
                answer+="L";
                num_L = numbers[i];
            }
            else if(length_R<length_L)
            {
                answer+="R";
                num_R = numbers[i];
            }
            else
            {
                if(hand =="left" )
                {
                     answer+="L";
                num_L = numbers[i];
                }
                else
                {
                       answer+="R";
                num_R = numbers[i];
                }
            }
            
        }
    }
    
    return answer;
}
