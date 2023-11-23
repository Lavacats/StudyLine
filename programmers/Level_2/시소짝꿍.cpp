#include <string>
#include <vector>
#include <map>
using namespace std;

long long solution(vector<int> weights) {
    long long answer = 0;
    map<long long,long long> map_wei;
    for(int i=0;i<weights.size();i++)
    {
        if(map_wei.find(weights[i])==map_wei.end())map_wei[weights[i]]=1;
        else map_wei[weights[i]]+=1;
    }
    for(const auto& pair: map_wei)
    {
        long long m_weight = pair.first;
        long long m_cnt = pair.second;
        
        if(m_cnt>1)answer+=((m_cnt*(m_cnt-1))/2);    // 1 : 1
        if(map_wei.find(m_weight*2)!=map_wei.end())answer+=map_wei[m_weight*2]*m_cnt;  // 1 : 2
        if(m_weight%2==0)
        {
            long long m_weight23 = (m_weight/2)*3;
            if(map_wei.find(m_weight23)!=map_wei.end())answer+=map_wei[m_weight23]*m_cnt; // 2 : 3
        }
        if(m_weight%3==0)
        {
            long long m_weight34 = (m_weight/3)*4;
            if(map_wei.find(m_weight34)!=map_wei.end())answer+=map_wei[m_weight34]*m_cnt; // 3 : 4
        }
    }
    return answer;
}
