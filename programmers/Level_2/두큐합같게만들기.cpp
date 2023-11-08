#include <string>
#include <vector>
#include <queue>
using namespace std;

int sumQueue(queue<int> q)
{
    int sum = 0;
    while (!q.empty())
    {
        sum += q.front();
        q.pop();
    }
    return sum;
}
int solution(vector<int> queue1, vector<int> queue2) {
    int answer = 0;
    long long sumQue_1=0;
    long long sumQue_2=0;
    queue<int> m_que1;
    queue<int> m_que2;

    for(int i=0;i<queue1.size();i++)m_que1.push(queue1[i]);
    for(int i=0;i<queue2.size();i++)m_que2.push(queue2[i]);
    
    sumQue_1 =sumQueue(m_que1);
    sumQue_2 =sumQueue(m_que2);
    
    while(true)
    {
        if(sumQue_2==sumQue_1)break;
        else if(sumQue_1>sumQue_2)
        {
            m_que2.push(m_que1.front());
            sumQue_1 -= m_que1.front();
            sumQue_2 += m_que1.front();
            m_que1.pop();
        }
        else if(sumQue_1<sumQue_2)
        {
            m_que1.push(m_que2.front());
            sumQue_2 -= m_que2.front();
            sumQue_1 += m_que2.front();
            m_que2.pop();
        }
        if(answer>(int)queue1.size()*3)
        {
            answer=-1;
            break;
        }
        answer++;
    }
    return answer;
}
