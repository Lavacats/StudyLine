#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


vector<int> solution(vector<int> numlist, int n) {
    vector<int> answer;
    vector<int> dummy = numlist;
    for(int i=0;i<dummy.size();i++)dummy[i]-=n;
    
    int numValue;
    for(int i=0;i<dummy.size();i++)
    {
        int indexValue=i;
        numValue=10000;
        for(int k=0;k<dummy.size();k++)
        {
            if(abs(dummy[k])<numValue)
            {
                indexValue = k;
                numValue = abs(dummy[k]);
            }
            if(abs(dummy[k])==numValue)
            {
                if(numlist[k]>numlist[indexValue])
                {
                    indexValue = k;
                }
            }
        }
        dummy[indexValue]=10000;
        answer.push_back(numlist[indexValue]);
    }
   
    
    return answer;
}
