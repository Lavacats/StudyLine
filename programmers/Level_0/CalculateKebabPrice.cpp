#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int n, int k) {
    int answer = 0;
    answer+=n*12000;
    int ser = n/10;
    answer += (k-ser)*2000;
    return answer;
}
