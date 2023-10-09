#include <string>
#include <vector>

using namespace std;

int solution(vector<int> sides) {
    int answer = 0;
    int minNum=sides[0];
    int maxNum=sides[1];
    if(sides[0]>sides[1])
    {
        minNum=sides[1];
        maxNum=sides[0];
    }
    for(int i=1;i<maxNum;i++)
    {
        if(i+minNum>maxNum)answer++;
    }
    for(int i=maxNum;i<(minNum+maxNum);i++)
    {
        if(i<minNum+maxNum)answer++;
    }
    return answer;
}
