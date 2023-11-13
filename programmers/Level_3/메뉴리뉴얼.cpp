#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    vector<int> maxCount;
    map<string,int> ordersMap;
    for(int i=0;i<course.size();i++)maxCount.push_back(0);
    for(int i=0;i<orders.size();i++)
    {
        sort(orders[i].begin(),orders[i].end());
        map<string,int> m_order;
        do{
            for(int j=0;j<course.size();j++)
            {
                string curString="";
                if(orders[i].size()<course[j])continue;
                curString = orders[i].substr(0,course[j]);
                sort(curString.begin(),curString.end());
                if(m_order.find(curString)==m_order.end())m_order[curString]=1;
            }
        } while(next_permutation(orders[i].begin(),orders[i].end()));
        for(const auto& pair:m_order)
        {
            if(ordersMap.find(pair.first)==ordersMap.end())ordersMap[pair.first]=1;
            else ordersMap[pair.first]++;
        }
    }
    for(const auto& pair:ordersMap)
    {
        for(int i=0;i<course.size();i++)
        {
            if(course[i]==(int)pair.first.size())
            {
                if(maxCount[i]<pair.second && pair.second>1)maxCount[i]=pair.second;
                break;
            }
        }
    }
    for(int i=0;i<course.size();i++)
    {
        vector<string> courOrder;
        for(const auto& pair:ordersMap)
        {
            if(course[i]==(int)pair.first.size())
            {
                if(maxCount[i]==0){}
                else if(maxCount[i]<pair.second)
                {
                    courOrder.clear();
                    maxCount[i]=pair.second;
                    courOrder.push_back(pair.first);
                }
                else if(maxCount[i]==pair.second)
                {
                    courOrder.push_back(pair.first);
                }
            }
        }
        for(int j=0;j<courOrder.size();j++)answer.push_back(courOrder[j]);
    }
    sort(answer.begin(),answer.end());
    return answer;
}
