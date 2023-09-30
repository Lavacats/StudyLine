#include <string>
#include <vector>

using namespace std;

int solution(int chicken) {
    int answer = 0;
    while(true)
    {
        int chiValue = chicken/10;
        answer+=chiValue;
        int minusValue = chicken - (chicken/10)*10;
        chicken=minusValue+chiValue;
        if(chicken<10)break;
    }
    return answer;
}
