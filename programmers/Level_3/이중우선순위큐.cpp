#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> solution(vector<string> operations) {
    vector<int> answer;
    vector<int> answerVec;
    
    for(int i=0;i<operations.size();i++)
    {
        
        if(operations[i][0]=='I')
        {
            int numberV=0;
            if(operations[i][2]=='-')
            {
                for(int j=3;j<operations[i].size();j++)
                {
                    numberV*=10;
                    numberV+=(operations[i][j]-'0');
                }
                numberV*=-1;
            }
            else
            {
                for(int j=2;j<operations[i].size();j++)
                {
                    numberV*=10;
                    numberV+=(operations[i][j]-'0');
                }
            }
            answerVec.push_back(numberV);
            sort(answerVec.begin(),answerVec.end());
        }
        else
        {
            if(operations[i][2]=='-')
            {
                if(answerVec.size()>0) answerVec.erase(answerVec.begin());
            }
            else
            {
                if(answerVec.size()>0) answerVec.erase(answerVec.begin()+answerVec.size()-1);
            }
        }
    }
    if(answerVec.size()==0)
    {
        answer.push_back(0);
        answer.push_back(0);
    }
    else if(answerVec.size()==1)
    {
        answer.push_back(answerVec[0]);
        answer.push_back(answerVec[0]);
    }
    else if(answerVec.size()>=2)
    {
        answer.push_back(answerVec[answerVec.size()-1]);
        answer.push_back(answerVec[0]);
    }
    return answer;
}
