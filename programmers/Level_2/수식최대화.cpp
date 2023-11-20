#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(string expression) {
    long long answer = 0;
    long long numValue=0;
    vector<long long> numVec;
    vector<char> perVec;
    vector<char> rankPer;
    
    rankPer.push_back('*');
    rankPer.push_back('+');
    rankPer.push_back('-');

    for(int i=0;i<expression.size();i++)
    {
        if(expression[i]>='0'&&expression[i]<='9')
        {
            numValue*=10;
            numValue+=(expression[i]-'0');
        }
        else
        {
            perVec.push_back(expression[i]);
            numVec.push_back(numValue);
            numValue = 0;
        }
        if(i==expression.size()-1)  numVec.push_back(numValue);
    }
    do {
        vector<long long> copyNum = numVec;
        vector<char> copyPer = perVec;
        for (int i = 0; i < rankPer.size(); i++)
        {
            int index=0;
            while(true)
            {
                if(index>=copyPer.size())break;
                
                if(rankPer[i]==copyPer[index])
                {
                    if(rankPer[i]=='-')
                    {
                        copyNum[index]-=copyNum[index+1];
                    }
                    else if(rankPer[i]=='+')
                    {
                        copyNum[index]+=copyNum[index+1];
                    }
                    else if(rankPer[i]=='*')
                    {
                        copyNum[index]*=copyNum[index+1];
                    }
                    copyNum.erase(copyNum.begin()+index+1);
                    copyPer.erase(copyPer.begin()+index);
                }else index++;
            }
        }
        if(answer<abs(copyNum[0]))answer=abs(copyNum[0]);
    } while (next_permutation(rankPer.begin(), rankPer.end()));
  

    return answer;
}
