#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

bool compareMapSize(const map<int, int>& map1, const map<int, int>& map2) {
    return map1.size() > map2.size();
}

pair<map<int, int>, map<int, int>> findLargestTwoMaps(const vector<map<int, int>>& maps) {
    // maps가 비어있으면 두 번째 맵을 빈 맵으로 반환
    if (maps.empty()) {
        return { {}, {} };
    }
    vector<map<int, int>> sortedMaps = maps;
    sort(sortedMaps.begin(), sortedMaps.end(), compareMapSize);

    return { sortedMaps[0], sortedMaps[1] };
}
int solution(vector<int> cards) {
    int answer = 0;
    vector<map<int,int>> cardBox;
    map<int,int> dummyCards;
    for(int i=0;i<cards.size();i++)dummyCards[i]=cards[i]-1;
    int index=0;
    while(true)
    {
        map<int,int> cardIndex;
        vector<int> vecIndex;
        if(dummyCards.empty())break;
        index = dummyCards.begin()->first;
        cardIndex[index]=1;
        vecIndex.push_back(index);
        while(true)
        {
            index=dummyCards[index];
            if(cardIndex.find(index)!=cardIndex.end())break;
            cardIndex[index]=1;
            vecIndex.push_back(index);
        }
        for(int i=0;i<vecIndex.size();i++)dummyCards.erase(vecIndex[i]);
        cardBox.push_back(cardIndex);
    }
    if(cardBox.size()<2)return 0;
    auto result = findLargestTwoMaps(cardBox);
    answer = result.first.size()*result.second.size();
    return answer;
}
