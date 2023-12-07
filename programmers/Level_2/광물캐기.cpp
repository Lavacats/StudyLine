#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


int solution(vector<int> picks, vector<string> minerals) {
    int answer = 0;
    map<int,int> mapCount;
    vector<int> pickVec;

    int index=0;
    
    for(int i=0;i<picks[0];i++)pickVec.push_back(3);
    for(int i=0;i<picks[1];i++)pickVec.push_back(2);
    for(int i=0;i<picks[2];i++)pickVec.push_back(1);
    
    for(int i=0;i<minerals.size();i++)
    {
        if(i!=0&& i%5==0 )index++;
        if(index==pickVec.size())break;
        if(minerals[i]=="diamond")mapCount[index]+=25;
        else if(minerals[i]=="iron")mapCount[index]+=5;
        else if(minerals[i]=="stone")mapCount[index]+=1;
    }
    while(true)
    {
        if(mapCount.size()==0)break;
        if(pickVec.size()==0)break;
        auto maxElement = max_element(mapCount.begin(), mapCount.end(),
                                           [](const auto& p1, const auto& p2) {
            return p1.second < p2.second;});
        
        if(pickVec[0]==3)
        {
            for(int i=0;i<5;i++)
            {
                if((i+maxElement->first*5)>=minerals.size())break;
                else
                {
                    answer++;
                }
            }
        }
        else if(pickVec[0]==2)
        {
            for(int i=0;i<5;i++)
            {
                if((i+maxElement->first*5)>=minerals.size())break;
                else
                {
                    if(minerals[i+maxElement->first*5]=="diamond")answer+=5;
                    else answer+=1;
                }
            }
        }
        else if(pickVec[0]==1)
        {
            for(int i=0;i<5;i++)
            {
                if((i+maxElement->first*5)>=minerals.size())break;
                else
                {
                    if(minerals[i+maxElement->first*5]=="diamond")answer+=25;
                    else if(minerals[i+maxElement->first*5]=="iron")answer+=5;
                    else answer+=1;
                }
            }
        }
        pickVec.erase(pickVec.begin()+0);
        mapCount.erase(mapCount.find( maxElement->first));
        
    }
    return answer;
}
