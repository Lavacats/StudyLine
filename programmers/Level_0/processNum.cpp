#include <string>
#include <vector>

using namespace std;

vector<int> solution(int num, int total) {
    vector<int> answer;
        int centerValue = 0;
        int cutValue = num/2;
        centerValue = total/num;
    
    if(num%2!=0)
    {
    
        for(int i=0;i<num;i++)
        {
              answer.push_back(centerValue+(i-cutValue));
        }
    }
    else
    {
        for(int i=0;i<num;i++)
        {
            answer.push_back(centerValue+(i-cutValue)+1);
        }
    }
    
    return answer;
}
