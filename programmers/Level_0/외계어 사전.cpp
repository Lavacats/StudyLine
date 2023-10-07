#include <string>
#include <vector>

using namespace std;

int solution(vector<string> spell, vector<string> dic) {
    int answer = 2;
    for(int i=0;i<dic.size();i++)
    {
        bool isCheck=true;
        vector<string> dummy = spell;
        
        for(int j=0;j<dic[i][j];j++)
        {
             for(int k=0;k<dummy.size();k++)
            {
               if(dummy[k][0] == dic[i][j])
               {
                   dummy[k]="0";
               }
            }
        }
        for(int i=0;i<dummy.size();i++)
        {
            if(dummy[i]!="0")isCheck=false;
        }
        if(isCheck) return 1;
       
    }
    return answer;
}
