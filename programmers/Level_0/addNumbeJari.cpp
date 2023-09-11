#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int n) {
    int answer = 0;
    int number=n;
    while(true)
    {
        answer+=number%10;
        number=number/10;
        if(number==0)break;
    }
    
    return answer;
}
