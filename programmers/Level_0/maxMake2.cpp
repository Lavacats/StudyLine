#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// numbers_len은 배열 numbers의 길이입니다.
int solution(int numbers[], size_t numbers_len) {
    int answer = -100000000;
    for(int i=0; i<numbers_len;i++)
    {
        for(int k=i;k<numbers_len;k++)
        {
            if(k!=i)
            {
                if(answer<(numbers[i]*numbers[k]))
                    answer = numbers[i]*numbers[k];
            }
        }
    }

    
    return answer;
}
