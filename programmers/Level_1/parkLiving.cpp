
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> park, vector<string> routes) {
    vector<int> answer;
    for(int i=0;i<park.size();i++)
    {
        for(int k=0;k<park[i].size();k++)
        {
            if(park[i][k]=='S')
            {
                int m_hor = i;
                int m_ver = k;
                for(int j=0;j<routes.size();j++)
                {
                    int pushNum = routes[j][2] - '0';
                    bool isCheck=true;
                    if(routes[j][0]=='E')
                    {
                        if((m_ver+pushNum)<park[m_hor].size())
                        {
                            for(int p=1;p<=pushNum;p++)
                            {
                                if(park[m_hor][m_ver+p]=='X')isCheck=false;
                            }
                            if(isCheck)m_ver+=pushNum;
                        }
                    }
                    else if(routes[j][0]=='W')
                    {
                        if((m_ver-pushNum)>=0)
                        {
                            for(int p=1;p<=pushNum;p++)
                            {
                                if(park[m_hor][m_ver-p]=='X')isCheck=false;
                            }
                            if(isCheck)m_ver-=pushNum;
                        }
                    }
                    else if(routes[j][0]=='N')
                    {
                        if((m_hor-pushNum)>=0)
                        {
                            for(int p=1;p<=pushNum;p++)
                            {
                                if(park[m_hor-p][m_ver]=='X')isCheck=false;
                            }
                            if(isCheck)m_hor-=pushNum;
                        }
                    }
                    else if(routes[j][0]=='S')
                    {
                         if((m_hor+pushNum)<park.size())
                        {
                            for(int p=1;p<=pushNum;p++)
                            {
                                if(park[m_hor+p][m_ver]=='X')isCheck=false;
                            }
                            if(isCheck)m_hor+=pushNum;
                        }
                    }
                }
                answer.push_back(m_hor);
                answer.push_back(m_ver);
                return answer;
            }
        }
    }
    return answer;
}
