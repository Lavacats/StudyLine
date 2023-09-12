#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char* solution(int age) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* answer = (char*)malloc(4*sizeof(char*));
    int dummy=0;
    int num1=0;
    int num2=0;
    int num3=0;
    
    if(age==1000) answer= "baaa";
    else if(age<1000 && age>=100)
    {
        num1=age/100;
        answer[0] = 'a'+num1;
        dummy=age%100;
        
        num2=dummy/10;
        answer[1] = 'a'+num2;
        dummy=dummy%10;
        
        answer[2] = 'a'+dummy;
        num3 = dummy;
        
        answer[3] = '\0';
    }
    else if(age<100 && age>=10)
    {
        num1 = age/10;
        answer[0] = 'a'+num1;
        dummy = age%10;
        
        answer[1] = 'a'+dummy;
        
        answer[2] = '\0';
    }
    else {
        answer[0]='a'+age;
        answer[1]='\0';
    }
    
    
    return answer;
}
