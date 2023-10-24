#include <string>
#include <vector>
#include <map>
using namespace std;
int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    int length = (int)want.size();
    int disCountlength = (int)discount.size();
    map<string,int> wantMap;
    for(int i=0;i<length;i++)wantMap[want[i]]=number[i];
    
    for(int i=0;i<disCountlength;i++)
    {
        map<string,int> discountMap;
        for(int j=0;j<10;j++)
        {
            if((i+j)<disCountlength)
            {
                if(discountMap.find(discount[i+j])==discountMap.end())discountMap[discount[i+j]]=1;
                else discountMap[discount[i+j]]+=1;
            }
        }
        bool isCheck=true;
        for (const auto& pair : wantMap)
        {
            if(discountMap.find(pair.first)!=discountMap.end())
            {
                if(wantMap[pair.first]!=discountMap[pair.first])isCheck=false;
            }
            else isCheck=false;
        }
        if(isCheck)answer++;
    }
    return answer;
}
