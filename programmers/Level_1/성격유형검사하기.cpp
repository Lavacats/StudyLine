#include <string>
#include <vector>
#include <map>
using namespace std;
string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    map<char,int> nameValue;
    nameValue['R']=0;
     nameValue['T']=0;
     nameValue['C']=0;
     nameValue['F']=0;
     nameValue['J']=0;
     nameValue['M']=0;
     nameValue['A']=0;
     nameValue['N']=0;
    for(int i=0;i<survey.size();i++)
    {
        if(choices[i]<4)
        {
            nameValue[survey[i][0]]+=abs(4-choices[i]);
        }
        else if(choices[i]>4)
        {
            nameValue[survey[i][1]]+=abs(4-choices[i]);
        }
    }
    if(nameValue['R']>nameValue['T'])answer.push_back('R');
    else if(nameValue['R']<nameValue['T'])answer.push_back('T');
    else answer.push_back('R');
    
    if(nameValue['C']>nameValue['F'])answer.push_back('C');
    else if(nameValue['C']<nameValue['F'])answer.push_back('F');
    else answer.push_back('C');
    
    if(nameValue['J']>nameValue['M'])answer.push_back('J');
    else if(nameValue['J']<nameValue['M'])answer.push_back('M');
    else answer.push_back('J');
    
    if(nameValue['A']>nameValue['N'])answer.push_back('A');
    else if(nameValue['A']<nameValue['N'])answer.push_back('N');
    else answer.push_back('A');
    
    return answer;
}
