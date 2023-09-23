#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    int curYear=(today[0]-'0')*1000+(today[1]-'0')*100+(today[2]-'0')*10+(today[3]-'0');
    int curMonth = (today[5]-'0')*10+(today[6]-'0');
    int curDay= (today[8]-'0')*10+(today[9]-'0');
    
    map<string,int> termMap;
    for(int i=0;i<terms.size();i++)
    {
        string m_code ;
        m_code += terms[i][0];
        int m_month = 0;
        for(int k=2;k<terms[i].size();k++)
        {
            m_month*=10;
            m_month+=(terms[i][k]-'0');
        }
        termMap[m_code]=m_month;
    }
    for(int i=0;i<privacies.size();i++)
    {
        int m_year=(privacies[i][0]-'0')*1000+(privacies[i][1]-'0')*100+(privacies[i][2]-'0')*10+(privacies[i][3]-'0');
        int m_month = (privacies[i][5]-'0')*10+(privacies[i][6]-'0');
        int m_day= (privacies[i][8]-'0')*10+(privacies[i][9]-'0');
        string m_code;
        m_code+= privacies[i][11];
        
        if(termMap.find(m_code)!=termMap.end())
        {
            int m_mon = termMap[m_code];
            int m_dayTime = m_mon*28;
      
           m_day+=m_dayTime;
            
            if(m_day>28)
            {
                if(m_day%28!=0)
                {
                    m_month +=(m_day/28);
                    m_day = m_day%28;
                }
                else
                {
                    m_month +=(m_day/28);
     
                    m_day = 1;
                }
            }
            if(m_month>12)
            {
                m_year+=(m_month/12);
                m_month = m_month%12;
                if(m_month==0)
                {   m_year--;
                    m_month=12;
                }
            }
          
            
            if(curYear>m_year)answer.push_back(i+1);
            else if((curYear==m_year)&&curMonth>m_month)answer.push_back(i+1);
            else if((curYear==m_year)&&(curMonth==m_month)&&curDay>=m_day)answer.push_back(i+1);
            
        }
    }
    
    return answer;
}
