#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int* solution(const char* my_string) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
   
    int length = strlen(my_string);
     int* answer = (int*)malloc(length*sizeof(int*));
    int index=0;
    for(int i=0; i<length;i++)
    {
        if(my_string[i]>='0'&&my_string[i]<='9')
        {
            answer[index] = my_string[i]-'0';
            index++;
        }
    }
    int* answer2 = (int*)malloc(1);
    for(int i=0;i<index;i++)
    {
        for(int k=i;k<index;k++)
        {
            int dummy=0;
            if(k!=0)
            {
                if(answer[i]>answer[k])
                {
                    dummy=answer[i];
                    answer[i] = answer[k];
                    answer[k] = dummy;
                }
            }
        }
    }
    
    return answer;
}
