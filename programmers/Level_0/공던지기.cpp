#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers, int k) {
    int answer = numbers[0];
    int index=0;
    for(int i=0;i<k;i++)
    {
        answer = numbers[index];
        index+=2;
        if(index>=(int)numbers.size())index-=(int)numbers.size();
       
    }
    return answer;
}
