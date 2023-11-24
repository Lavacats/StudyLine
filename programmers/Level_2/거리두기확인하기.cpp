#include <string>
#include <vector>

using namespace std;
vector<int> solution(vector<vector<string>> places)
{
    vector<int> answer;
    for(int i=0;i<places.size();i++)
    {
        bool isCheck=true;
        for(int j=0;j<places[i].size();j++)
        {
            for(int k=0;k<places[i][j].size();k++)
            {
                if(places[i][j][k]=='P')
                {
                    bool m_up = false;
                    bool m_left = false;
                    bool m_right = false;
                    bool m_down = false;
                    
                    // 상하좌우 , 2칸 체크
                    if(j>0)
                    {
                        if(places[i][j-1][k]=='P')isCheck=false;
                        else if(places[i][j-1][k]=='X')m_up=true;
                    }
                    if(j>1)
                    {
                        if(places[i][j-2][k]=='P')
                        {
                            if(!m_up) isCheck=false;
                        }
                    }
                    
                    if(j<(places[i].size()-1))
                    {
                        if(places[i][j+1][k]=='P') isCheck=false;
                        else if(places[i][j+1][k]=='X')m_down=true;
                    }
                    if(j<(places[i].size()-2))
                    {
                        if(places[i][j+2][k]=='P')
                        {
                            if(!m_down)isCheck=false;
                        }
                    }
                    
                    if(k>0)
                    {
                        if(places[i][j][k-1]=='P')isCheck=false;
                        else if(places[i][j][k-1]=='X')m_left=true;
                    }
                    if(k>1)
                    {
                        if(places[i][j][k-2]=='P')
                        {
                            if(!m_left)isCheck=false;
                        }
                    }
                    
                    if(k<(places[i][j].size()-1))
                    {
                        if(places[i][j][k+1]=='P')isCheck=false;
                        else if(places[i][j][k+1]=='X')m_right=true;
                    }
                    if(k<(places[i][j].size()-2))
                    {
                        if(places[i][j][k+2]=='P')
                        {
                            if(!m_right)isCheck=false;
                        }
                    }
                    // 대각선 체크
                    // 좌상
                    if(j>0 && k>0)
                    {
                        if(places[i][j-1][k-1]=='P')
                        {
                            if(!m_left||!m_up)isCheck=false;
                        }
                    }
                    // 좌하
                    if(j<(places[i].size()-1)  && k>0)
                    {
                        if(places[i][j+1][k-1]=='P')
                        {
                            if(!m_left||!m_down)isCheck=false;
                        }
                    }
                    // 우상
                    if(j>0 &&k<(places[i][j].size()-1))
                    {
                        if(places[i][j-1][k+1]=='P')
                        {
                            if(!m_right||!m_up)isCheck=false;
                        }
                    }
                    // 우하
                    if(j<(places[i].size()-1) &&k<(places[i][j].size()-1))
                    {
                        if(places[i][j+1][k+1]=='P')
                        {
                            if(!m_right||!m_down)isCheck=false;
                        }
                    }
                }
                if(!isCheck)break;
            }
            if(!isCheck)break;
        }
        answer.push_back(isCheck);
    }
    return answer;
}
