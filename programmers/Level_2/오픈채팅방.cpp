#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string,string> m;
    for(int i=0;i<record.size();i++)
    {
        vector<string> v;
        string str;
        for(int j=0;j<record[i].length();j++)
        {
            if(record[i][j]==' ')
            {
                v.push_back(str);
                str="";
            }
            else
            {
                str+=record[i][j];
                if(j+1==record[i].length())
                    v.push_back(str);
            }
        }
        
        if(record[i][0]=='E')
        {
            if(m.find(v[1])!=m.end())
                m[v[1]]=v[2];
            else
                m.insert(pair<string,string>(v[1],v[2]));
        }
        else if(record[i][0]=='C')
            m[v[1]]=v[2];    
    }
    
    for(int i=0;i<record.size();i++)
    {
        vector<string> v;
        string str;
        for(int j=0;j<record[i].length();j++)
        {
            if(record[i][j]==' ')
            {
                v.push_back(str);
                str="";
            }
            else
            {
                str+=record[i][j];
                if(j+1==record[i].length())
                    v.push_back(str);
            }
        }
        
        
        if(record[i][0]=='E')
            answer.push_back(m[v[1]]+"님이 들어왔습니다.");
        else if(record[i][0]=='L')
            answer.push_back(m[v[1]]+"님이 나갔습니다.");
 
    }
    return answer;
}
