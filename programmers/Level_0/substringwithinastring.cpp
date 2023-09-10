#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* str1, const char* str2) {
    int answer = 2;
    size_t length_1 = strlen(str1);
    size_t length_2 = strlen(str2);
    for(int i=0; i<length_1;i++)
    {
        if(str1[i] == str2[0])
        {   
            if(i+length_2 <= length_1)
            {
                bool check=true;
                for(int k=0;k<length_2;k++)
                {
                    if(str1[i+k]!=str2[k])
                    {
                        check=false;
                    }
                }
                if(check)answer = 1;
            }
        }
    }
    
    
    return answer;
}
