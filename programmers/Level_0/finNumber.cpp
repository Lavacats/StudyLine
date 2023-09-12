#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int num, int k) {
    int answer = 0;
    int length=0;
    int index=-1;
    while(true)
    {
        if((num%10)==k)index = length;
        num = num / 10;
        length++;
    
        if(num==0)break;
    }
    if(index==-1) return -1;
    else
    {
        answer = length - index;
        return answer;
    }
}
