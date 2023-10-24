#include <string>
#include <vector>

using namespace std;
vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    long long leftX=left%n;
    long long leftY=left/n;
    long long rightX=right%n;
    long long rightY=right/n;
    for(long long i=leftY;i<=rightY;i++)
    {
        long long index=0;
        for(int j=0;j<n;j++)
        {
            long long pushValue=0;
            if(j<=i)
            {
                pushValue=i+1;
                index=i+1;
            }
            else
            {
                index++;
                pushValue=index;
            }
            long long curIndex = i*n+j;
            if(curIndex>=left && curIndex<=right)answer.push_back(pushValue);
        }
    }
    return answer;
}
