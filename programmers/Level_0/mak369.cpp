#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int order) {
    int answer = 0;
    while(true)
    {
        if(order%10 == 3 ||order%10 == 6||order%10 == 9 )answer++;
        order = order/10;
        if(order==0)return answer;
        
    }
    return answer;
}
