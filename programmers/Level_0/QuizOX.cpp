#include <string>
#include <vector>

using namespace std;

vector<string> solution(vector<string> quiz) {
    vector<string> answer;
    for(int k=0;k<quiz.size();k++)
    {
    bool isEqual = false;
    int giho1=1;
    int giho2=1;
    int giho3=1;
    int m_num1=10001;
    int dummy1=0;
    int m_num2=10001;
    int dummy2=0;
    int m_num3=20001;
    int dummy3=0;
    for(int i=0;i<quiz[k].size();i++)
    {
        if(m_num1==10001)
        {
            if(quiz[k][i]==' ')
            {
               m_num1 = dummy1*giho1;
            }
            else if(quiz[k][i]=='-')
            {
                giho1 *= -1;
            }
            else if(quiz[k][i]>='0'&&quiz[k][i]<='9')
            {
                dummy1*=10;
                dummy1+=quiz[k][i]-'0';
            }
        }
        else if(m_num1!=10001&&m_num2==10001)
        {
            if(quiz[k][i]=='=')
            {
               m_num2 = dummy2*giho2;
            }
            else if(quiz[k][i]=='-')
            {
                giho2 *= -1;
            }
            else if(quiz[k][i]>='0'&&quiz[k][i]<='9')
            {
                dummy2*=10;
                dummy2+=quiz[k][i]-'0';
            }
        }
        else if(m_num1!=10001&&m_num2!=10001)
        {
            if(quiz[k][i]=='-')
            {
                giho3 = -1;
            }
            else if(quiz[k][i]>='0'&&quiz[k][i]<='9')
            {
                dummy3*=10;
                dummy3+=quiz[k][i]-'0';
            }
        }
    
    }
            if((m_num1+m_num2)==giho3*dummy3)answer.push_back("O");
            else answer.push_back("X");
    }
    return answer;
}
