#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* my_string) {
    int answer = 0;
    int length=strlen(my_string);
    for(int i=0; i<length;i++)
    {
        if(my_string[i]>='0' && my_string[i]<='9')
        {
            if(my_string[i]=='1')answer+=1;
             if(my_string[i]=='2')answer+=2;
             if(my_string[i]=='3')answer+=3;
             if(my_string[i]=='4')answer+=4;
             if(my_string[i]=='5')answer+=5;
             if(my_string[i]=='6')answer+=6;
             if(my_string[i]=='7')answer+=7;
             if(my_string[i]=='8')answer+=8; 
             if(my_string[i]=='9')answer+=9;
        }
    }
    return answer;
}
