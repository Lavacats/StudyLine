#include <string>
#include <vector>
#include <map>
using namespace std;

struct Compare
{
    bool operator()(const int& a, const int& b) const
    {
        return a > b;
    }
};

vector<int> solution(vector<string> genres, vector<int> plays)
{
    vector<int> answer;
    map<string,int> genreMap;             // 장르  : 총시간
    map<int, string, Compare> allTimeMap; // 총시간 : 장르
    map<string,map<int, vector<int>, Compare>> timeMap;    // 시간  : 인덱스
    
    for(int i=0;i<genres.size();i++)
    {
        if(genreMap.find(genres[i])==genreMap.end())genreMap[genres[i]]=plays[i];
        else genreMap[genres[i]]+=plays[i];
        
        if(timeMap.find(genres[i])==timeMap.end())
        {
            map<int,vector<int>,Compare> timeIndex;
            timeIndex[plays[i]].push_back(i);
            timeMap[genres[i]] = timeIndex;
        }
        else timeMap[genres[i]][plays[i]].push_back(i);
    }
    for(const auto& pair:genreMap)allTimeMap[pair.second] = pair.first;
    
    for(const auto& pair:allTimeMap)
    {
        int m_cnt=0;
        for(const auto& pairSong : timeMap[pair.second])
        {
            for(int i=0;i<pairSong.second.size();i++)
            {
                answer.push_back(pairSong.second[i]);
                m_cnt++;
                if(m_cnt>1)break;
            }
            if(m_cnt>1)break;
        }
    }
    return answer;
}
