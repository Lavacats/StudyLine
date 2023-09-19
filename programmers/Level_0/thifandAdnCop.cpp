#include <string>
#include <vector>
#include <map>
using namespace std;

bool findVector(vector<string> id_list,string name)
{
    bool result=false;
    for(int i=0;i<id_list.size();i++)
    {
        if(id_list[i]==name)result=true;
    }
    return result;
}

vector<int> solution(vector<string> id_list, vector<string> report, int ka) {
    vector<int> answer;
    map <string,vector<string>> userMap;
    map <string,vector<string>> banMap;
    map <string,int> comBan;
    
    for(int i=0;i<id_list.size();i++)
    {
        vector<string> str;
        banMap[id_list[i]]=str;
        comBan[id_list[i]]=0;
    }
    for(int i=0;i<report.size();i++)
    {
        string name_1;
        bool isCheck=true;
        string name_2;
        for(int k=0;k<report[i].size();k++)
        {
            if(report[i][k]==' ')isCheck=false;
            else if(isCheck)name_1+=report[i][k];
            else if(!isCheck)name_2+=report[i][k];
        }
        if(userMap.find(name_1)!=userMap.end())
        {
            auto userBan = userMap[name_1];
            if(!findVector(userBan,name_2))
            {
                userMap[name_1].push_back(name_2);
            }
        }
        else
        {
            userMap[name_1].push_back(name_2);
        }
    }
    for (const auto& pair : userMap)
    {
        for (const auto& pair2 : pair.second)
        {
            banMap[pair2].push_back(pair.first);
        }
    }
    for(const auto& pair : banMap)
    {
        if(pair.second.size()>=ka)
        {
            for(int i=0; i<pair.second.size();i++)
            {
                comBan[pair.second[i]]+=1;
            }
        }
    }
    for(int i=0;i<id_list.size();i++)
    {
        if(comBan.find(id_list[i])!=comBan.end())
            answer.push_back(comBan[id_list[i]]);
        else
            answer.push_back(0);
    }
  
  
    return answer;
}
