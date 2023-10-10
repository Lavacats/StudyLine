#include <string>
#include <vector>

using namespace std;


string solution(string new_id) {
    string answer = new_id;
    bool isCheck=true;
    if(new_id.length()<3||new_id.length()>15)
    {
        bool isEnd=false;
        for(int i=0;i<new_id.length();i++)
        {
            if(new_id[i] !='-'&& new_id[i] !='_' && new_id[i] !='.'&&
             (new_id[i]<'a' || new_id[i]>'z') &&(new_id[i]<'0' || new_id[i]>'9'))
                isCheck=false;

            
            if(new_id[i]=='.')
            {
                if(!isEnd)isEnd=true;
                else isCheck=false;
            }
            else
            {
                isEnd=false;
            }
            if(!isCheck)break;
            
        }
        if(new_id[0]=='.')isCheck=false;
        if(new_id[new_id.length()-1]=='.')isCheck=false;
    }
    else
    {
        isCheck=false;
    }
    // 대문자 변환

    {
        
        
        string solAnswer_1="";
        for(int i=0;i<new_id.length();i++)
        {
            if(new_id[i]>='A' && new_id[i]<='Z') solAnswer_1.push_back(new_id[i]-'A'+'a');
            else solAnswer_1.push_back(new_id[i]);
        }
        // 잡문자 제거
        string solAnswer_2="";
        for(int i=0;i<solAnswer_1.length();i++)
        {
            if(solAnswer_1[i] =='-'|| solAnswer_1[i] =='_' || solAnswer_1[i] =='.'||(solAnswer_1[i]>='a' && solAnswer_1[i]<='z')||(new_id[i]>='0' && new_id[i]<='9') )
                solAnswer_2.push_back(solAnswer_1[i]);
        }
        //.. 중복제거
        string solAnswer_3="";
        bool is3End = false;
        for(int i=0;i<solAnswer_2.length();i++)
        {
            if(solAnswer_2[i] =='.')
            {
                if(!is3End)
                {
                    is3End=true;
                    solAnswer_3.push_back(solAnswer_2[i]);
                }
            }
            else
            {
                solAnswer_3.push_back(solAnswer_2[i]);
                is3End=false;
            }
        }
        // . 앞뒤 제거
        string solAnswer_4="";
        for(int i=0;i<solAnswer_3.length();i++)
        {
            if(i==0)
            {
                if(solAnswer_3[i]!='.')solAnswer_4.push_back(solAnswer_3[i]);
            }
            else if(i==solAnswer_3.size()-1)
            {
                if(solAnswer_3[i]!='.')solAnswer_4.push_back(solAnswer_3[i]);
            }
            else
            {
                solAnswer_4.push_back(solAnswer_3[i]);
            }
        }
        //case 5
        if(solAnswer_4.size()==0)solAnswer_4.push_back('a');
        //case 6
        string solAnswer_5="";
        for(int i=0;i<solAnswer_4.length();i++)
        {
            if(i<15)
            {
                if(i==14)
                {
                    if(solAnswer_4[i]!='.') solAnswer_5.push_back(solAnswer_4[i]);
                }
                else
                {
                    solAnswer_5.push_back(solAnswer_4[i]);
                }
            }
        }
        // case 7
        if(solAnswer_5.size()<3)
        {
            char dummy = solAnswer_5[solAnswer_5.size()-1];
            for(int i=(int)solAnswer_5.size();i<3;i++)
            {
                solAnswer_5.push_back(dummy);
            }
        }
        answer=solAnswer_5;
    }
    return answer;
}
