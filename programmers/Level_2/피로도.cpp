#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    vector<pair<int,int>> incountD;
    vector<int> indexD;
    for(int i=0;i<dungeons.size();i++)
    {
        incountD.push_back({dungeons[i][0],dungeons[i][1]});
        indexD.push_back(i);
    }
    
   do{
        int dugeonC = k;
        int countValue = 0;        
        for(int i=0; i<indexD.size(); i++)
        {
            if(dugeonC >= incountD[indexD[i]].first)
            {
                countValue++;
                dugeonC -= incountD[indexD[i]].second;
            } 
        }
        answer = max(answer, countValue);
    } while(next_permutation(indexD.begin(),indexD.end()));
    

    
    return answer;
}
