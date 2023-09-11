#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// array_len은 배열 array의 길이입니다.
int solution(int array[], size_t array_len) {
    int answer = 0;

    for(int i=0; i<array_len;i++)
    {
        int minCount=0;
        int maxCount=0;
        for(int k=0;k<array_len;k++)
        {
            if(array[k]!=array[i])
            {
                if(array[i]>array[k])minCount++;
                if(array[i]<array[k])maxCount++;
            }
            
        }
       if(minCount==maxCount)return array[i];
    }
    
    
    return answer;
}
