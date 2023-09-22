#include <string>
#include <vector>

using namespace std;

int solution(string A, string B) {
    int answer = -1;
    for(int i=0;i<A.size();i++)
    {
        bool isCheck=true;
        for(int j=0;j<B.size();j++)
        {
            int value = j-i;
            if(value<0)value+=B.size();
            if(B[j]!=A[value])isCheck=false;
        }
        if(isCheck==true)
        {
            answer=i;
            break;
        }
    }
    return answer;
}
