#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// numbers_len은 배열 numbers의 길이입니다.
int solution(int numbers[], size_t numbers_len) {
    int answer = 0;
    int maxNum =numbers[0];
    int maxNum2 = numbers[1];
    for(int i=0; i<numbers_len;i++)
    {
        if(maxNum<numbers[i])maxNum = numbers[i];
    }
    if(maxNum2 == maxNum)maxNum2 = numbers[0];
    for(int i=0; i<numbers_len;i++)
    {
        if(maxNum2<numbers[i] && numbers[i]!=maxNum)
            maxNum2 = numbers[i];
    }
    return maxNum*maxNum2;
}
