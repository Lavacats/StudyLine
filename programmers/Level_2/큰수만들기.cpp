#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int numLength =number.size()-k;
    int countNum = k;
    while(true)
    {
        int maxNum =number[0];
        int index=0;
        for(int i=1;i<=countNum;i++)
        {
            if(number[i]>maxNum)
            {
                index=i;
                maxNum=number[i];
            }
        }
        if(index!=0)countNum-=index;
       
        answer.push_back(number[index]);
        number = number.substr(index+1,number.size()-1);
        
        if(number=="" || (answer.size()==numLength))break;
        if(countNum<=0 )
        {
            answer+=(number);
            break;
        }
        
    }
    return answer;
}
