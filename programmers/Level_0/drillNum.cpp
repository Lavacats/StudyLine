#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    for(int i=0;i<n;i++)
    {
        vector<int> dummy1;
        for(int k=0;k<n;k++)dummy1.push_back(0);
        answer.push_back(dummy1);
    }
    
    int index_VL=0;
    int index_VR=n-1;
    int index_HU=0;
    int index_HD=n-1;
    int index=1;
    while(true)
    {
        for(int i=index_VL;i<index_VR+1;i++)
        {
            if(answer[index_HU][i]==0)
            {
            answer[index_HU][i]=index;
            index++;
            }
        }
        index_HU++;
        for(int i=index_HU;i<index_HD;i++)
        {
            if(answer[i][index_VR]==0)
            {
            answer[i][index_VR]=index;
            index++;
            }
        }
        index_VR--;
        for(int i=index_VR+1;i>=index_VL;i--)
        {
            if( answer[index_HD][i]==0)
            {
            answer[index_HD][i]=index;
            index++;
        }
        }
        index_HD--;
         for(int i=index_HD;i>=index_HU;i--)
        {
             if(answer[i][index_VL]==0)
             {
            answer[i][index_VL]=index;
            index++;
        }}
        index_VL++;
        if(index_VL>index_VR && index_HU>index_HD)break;
    }
    
    
    
    return answer;
}
