#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    int mainTime    = fees[0];// 기본시간
    int mainfee     = fees[1];// 기본료
    int plusTime    = fees[2];// 추가시간
    int plusfee     = fees[3];// 추가료
    
    map<string,vector<string>> recordsMap;
    for(int i=0;i<records.size();i++)
    {
        string m_time = records[i].substr(0,5);
        string carNum = records[i].substr(6,4);
        
        recordsMap[carNum].push_back(m_time);
    }
    for(const auto& record:recordsMap)
    {
        vector<string> recordLine = record.second;
        if(recordLine.size()%2==1) recordLine.push_back("23:59");
        int totalFee=0;
        int sumTime=0;
        for(int i=0;i<recordLine.size()-1;i+=2)
        {
            int m_hour_1 = (recordLine[i][0]-'0')*10 + (recordLine[i][1]-'0');
            int m_min_1 =(recordLine[i][3]-'0')*10 + (recordLine[i][4]-'0');
            int m_hour_2 = (recordLine[i+1][0]-'0')*10 + (recordLine[i+1][1]-'0');
            int m_min_2 =(recordLine[i+1][3]-'0')*10 + (recordLine[i+1][4]-'0');
            
            sumTime+=(m_hour_2*60+m_min_2 -m_hour_1*60-m_min_1);
        }
        if(sumTime>mainTime)
        {
            sumTime-=mainTime;
            if(sumTime%plusTime==0)totalFee+=(sumTime/plusTime)*plusfee;
            else totalFee+=(sumTime/plusTime +1)*plusfee;
        }
        totalFee+=mainfee;
        answer.push_back(totalFee);
    }
    
    return answer;
}
