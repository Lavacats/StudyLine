#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// dots_rows는 2차원 배열 dots의 행 길이, dots_cols는 2차원 배열 dots의 열 길이입니다.
int solution(int** dots, size_t dots_rows, size_t dots_cols) {
    int answer=0;
    
    double a=dots[0][0]-dots[1][0];
    double b=dots[0][1]-dots[1][1];
    double c=dots[2][0]-dots[3][0];
    double d=dots[2][1]-dots[3][1];
    
    if(a/b==c/d) return 1;
    
    a=dots[0][0]-dots[2][0];
    b=dots[0][1]-dots[2][1];
    c=dots[1][0]-dots[3][0];
    d=dots[1][1]-dots[3][1];
    
    if(a/b==c/d) return 1;
    
    a=dots[0][0]-dots[3][0];
    b=dots[0][1]-dots[3][1];
    c=dots[1][0]-dots[2][0];
    d=dots[1][1]-dots[2][1];
    
    if(a/b==c/d) return 1;
    
    
    return 0;

 

}
