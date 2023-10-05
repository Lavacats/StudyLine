#include <string>
#include <vector>
#include <map>

using namespace std;



vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer;
    map<int,string> rankName;
    map<string,int> nameRank;
    for(int i=0;i<players.size();i++)
    {
        rankName[i+1]=players[i];
        nameRank[players[i]]=i+1;
    }
    for(int i=0;i<callings.size();i++)
    {
        int curRank = nameRank[callings[i]];
        nameRank[callings[i]]--;
        string prevPlayer = rankName[curRank-1];
        nameRank[prevPlayer]++;
        rankName[curRank]=prevPlayer;
        rankName[curRank-1] = callings[i];
    }
    for(int i=0;i<players.size();i++)
    {
        answer.push_back(rankName[i+1]);
    }
    return answer;
}
