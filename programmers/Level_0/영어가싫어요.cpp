#include <string>
#include <vector>

using namespace std;

long long solution(string numbers) {
    long long answer = 0;
    for(int i=0; i<numbers.size();i++)
    {
        if(numbers[i]=='z')
        {
            answer*=10;
            i+=3;
        }
        else  if(numbers[i]=='o')
        {
            answer*=10;
            answer++;
            i+=2;
        }
        else  if(numbers[i]=='t')
        {
             answer*=10;
            if(numbers[i+1]=='w')
            {
                answer+=2;
                i+=2;
            }
            else
            {
                answer+=3;
                i+=4;
            }
        } 
        else  if(numbers[i]=='f')
        {
             answer*=10;
            if(numbers[i+1]=='o')
            {
                answer+=4;
                i+=3;
            }
            else
            {
                answer+=5;
                i+=3;
            }
        } 
        else  if(numbers[i]=='s')
        { 
            answer*=10;
            if(numbers[i+1]=='i')
            {
                answer+=6;
                i+=2;
            }
            else
            {
                answer+=7;
                i+=4;
            }
        }
        else  if(numbers[i]=='e')
        {
            answer*=10;
            answer+=8;
            i+=4;
        }
        else  if(numbers[i]=='n')
        {
             answer*=10;
            answer+=9;
            i+=3;
        }
    }
    return answer;
}
