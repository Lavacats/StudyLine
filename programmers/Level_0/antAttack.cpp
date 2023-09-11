#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int hp) {
    int answer = 0;
    int curHp = hp;
        
    answer+=(hp/5);
    curHp = hp%5;
    answer+=(curHp/3);
    curHp = curHp%3;
    answer+=curHp;
    
    
    return answer;
}
