#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// babbling_len은 배열 babbling의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* babbling[], size_t babbling_len) {
    int answer = 0;
    
    for(int i=0; i<babbling_len;i++)
    {
        int length = strlen(babbling[i]);
        int count=0;
        for(int k=0;k<length;k++)
        {
            if(babbling[i][k]=='a')
            {
                if(k+2<length)
                {
                    if(babbling[i][k+1]=='y'&&babbling[i][k+2]=='a')
                    {
                        count+=3;
                        k+=2;
                    }
                }
            }
            else if(babbling[i][k]=='y')
            {
                if(k+1<length)
                {
                    if(babbling[i][k+1]=='e')
                    {
                        count+=2;
                        k++;
                    }
                }
            }
            else if(babbling[i][k]=='w')
            {
                if(k+2<length)
                {
                    if(babbling[i][k+1]=='o'&&babbling[i][k+2]=='o')
                    {
                        count+=3;
                        k+=2;
                    }
                }
            }
            else if(babbling[i][k]=='m')
            {
                if(k+1<length)
                {
                    if(babbling[i][k+1]=='a')
                    {
                        count+=2;
                        k++;
                    }
                }
            }
        }
        
        if(length==count)answer++;
    }
    return answer;
}
