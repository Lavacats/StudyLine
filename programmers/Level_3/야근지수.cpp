#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

long long solution(int n, vector<int> works)
{
    long long answer = 0;
    int index=0;
    priority_queue<int> maxHeap;
    for(int i=0;i<works.size();i++)maxHeap.push(works[i]);
    while(true)
    {
        int value = 0;
        if(maxHeap.top()>0)value=maxHeap.top()-1;
        maxHeap.pop();
        maxHeap.push(value);
        index++;
        if(index==n)break;
    }
    while (!maxHeap.empty())
    {
        answer+=maxHeap.top()*maxHeap.top();
        maxHeap.pop(); // 최대값 제거
    }
    return answer;
}
