#include <string>
#include <vector>

using namespace std;

int solution(string my_string) {
    int answer = 0;
    int num_1=0;
    bool isCheck=false;
    bool isPlus=true;
    for(int i=0;i<my_string.size();i++)
    {
        if(my_string[i]=='+'||my_string[i]=='-')
        {
            if(my_string[i]=='+')
            {
                isPlus=true;
            }
            else
            {
                isPlus = false;
            }
            answer+=num_1;
            num_1=0;
        }
        else if(my_string[i]!=' ')
        {
            if(!isCheck)
            {
                num_1*=10;
                if(isPlus)num_1+=(my_string[i]-'0');
                else num_1-=(my_string[i]-'0');
            }
        }
    }
     answer+=num_1;
    return answer;
}
