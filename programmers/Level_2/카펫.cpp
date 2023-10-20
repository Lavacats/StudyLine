#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    map<int,int> yellowType;
    map<int,int> brownType;
    for(int i=1;i<=sqrt(yellow);i++)
    {
        if(yellow%i==0)yellowType[i] = yellow/i;
    }
    for(int i=1;i<=sqrt(brown+yellow);i++)
    {
        if((brown+yellow)%i==0)brownType[i] = (brown+yellow)/i;
    }
    
    for (const auto& pairY : yellowType) 
    {
          for (const auto& pairB : brownType) 
          {
              if((pairY.first+2)<=pairB.first)
              {
                 if((pairY.second+2)<=pairB.second)
                 {
                     if(pairB.first<pairB.second)
                     {
                        answer.push_back(pairB.second);
                        answer.push_back(pairB.first);
                     }
                     else
                     {
                         answer.push_back(pairB.first);
                         answer.push_back(pairB.second);
                     }
                     return answer;
                 }
              }
          }
    }
    return answer;
}
