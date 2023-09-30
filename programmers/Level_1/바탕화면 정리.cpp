#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> wallpaper) {
    vector<int> answer;
    int min_X=-1;
    int max_X=wallpaper[0].size();
    int min_Y=-1;
    int max_Y=wallpaper.size();
    
    for(int i=0; i<wallpaper.size();i++)
    {
        for(int k=0;k<wallpaper[i].size();k++)
        {
            if(wallpaper[i][k]=='#')
            {
                if(min_X<0)min_X=k;
                else if(k<min_X)min_X=k;
                
                if(min_Y<0)min_Y=i;
                else if(i<min_Y)min_Y=i;
                
                 if(max_X==wallpaper[i].size())max_X=k;
                else if(k>max_X)max_X=k;
                
                if(max_Y==wallpaper.size())max_Y=i;
                else if(i>max_Y)max_Y=i;
            }
        }
    }
    answer.push_back(min_Y);
    answer.push_back(min_X);
    answer.push_back(max_Y+1);
    answer.push_back(max_X+1);
    return answer;
}
