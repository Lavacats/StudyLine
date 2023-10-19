#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(int n) {
    int answer = 0;
    map<int,int> solutionMap;
    solutionMap[0]=0;
    solutionMap[1]=1;
    int index=2;
    while(true)
    {
        long sumValue = solutionMap[index-1]+solutionMap[index-2];
        sumValue %= 1234567;
        solutionMap[index]=sumValue;
        
        if(index==n)break;
        else index++;
        
    }
    answer = solutionMap[index];
    return answer;
}
