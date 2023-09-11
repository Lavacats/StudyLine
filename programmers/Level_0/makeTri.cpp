#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// sides_len은 배열 sides의 길이입니다.
int solution(int sides[], size_t sides_len) {
    int answer = 0;
    int maxNum=0;
    int sumNum=0;
    for(int i=0;i<3;i++)
    {
        if(maxNum<sides[i])
        {
            maxNum=sides[i];
        }
        sumNum+=sides[i];
    }
    sumNum-=maxNum;
    
    if(maxNum <sumNum)answer= 1;
    else answer= 2;
    
    return answer;
}
