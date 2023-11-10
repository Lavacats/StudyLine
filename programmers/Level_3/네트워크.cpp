#include <string>
#include <vector>
#include <map>
using namespace std;

void checkCom(vector<int>& numVec,vector<vector<int>>& computers,map<int,int>& netMem,int index)
{
    for(int i=0;i<computers[index].size();i++)
    {
        if(computers[index][i]!=0)
        {
            if(netMem.find(i)==netMem.end())
            {
                netMem[i]=1;
                numVec[i]=0;
                computers[index][i]=0;
                if(i!=index)checkCom(numVec,computers,netMem,i);
            }
        }
    }
}

int solution(int n, vector<vector<int>> computers)
{
    int answer = 0;
    vector<int> numList;
 
    for(int i=1;i<=n;i++)numList.push_back(i);
    int m_index=0;
    while(true)
    {
        map<int,int> netWorkmem;
        int value = numList[m_index];
        if(value==0)m_index++;
        else
        {
            checkCom(numList,computers,netWorkmem,m_index);
            answer++;
        }
        if(m_index>=numList.size())break;
    }
    return answer;
}
