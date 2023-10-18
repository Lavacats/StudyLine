#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    int collectNum=0;
    int zeroNum=0;
    map<int,int> winMap;
    for(int i=0;i<win_nums.size();i++)winMap[win_nums[i]]=1;
    for(int i=0;i<lottos.size();i++)
    {
        if(lottos[i]!=0)
        {
            if(winMap.find(lottos[i])!=winMap.end())
            {
                collectNum++;
            }
        }
        else
        {
            zeroNum++;
        }
    }
    
    int rank_max = 7-(collectNum+zeroNum);
    if(rank_max>6)rank_max=6;
    
    int rank_min = 7-collectNum;
    if(rank_min>6)rank_min=6;
    
    answer.push_back(rank_max);
    answer.push_back(rank_min);
    return answer;
}
