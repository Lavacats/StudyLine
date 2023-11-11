#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    int valueNS = s/n;
    if(valueNS!=0)
    {
        int nsValue = s%n;
        for(int i=0;i<n;i++)answer.push_back(valueNS);
        for(int i=0;i<nsValue;i++)answer[i]+=1;
        sort(answer.begin(),answer.end());
    }
    else answer.push_back(-1);
    return answer;
}
