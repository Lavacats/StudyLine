#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int solution(int n, int k, vector<int> enemy) {
    int answer = 0;
    priority_queue<int> maxHeap;
    for(int i=0;i<enemy.size();i++)
    {
        n-=enemy[i];
        maxHeap.push(enemy[i]);
        if(n<=0)
        {
            while(true)
            {
                if(n>=0)break;
                if(k==0)break;
                n+=maxHeap.top();
                k--;
                maxHeap.pop();
               
            }
        }
        if(n<0)break;
        answer++;
    }
    return answer;
}

