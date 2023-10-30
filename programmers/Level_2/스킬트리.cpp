#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    map<char,int> skillmap;
    for(int i=0;i<skill.size();i++)skillmap[skill[i]]=i;
   
    for(int i=0;i<skill_trees.size();i++)
    { 
        int skillIndx=0;
        bool isCheck=true;
        for(int j=0;j<skill_trees[i].size();j++)
        {
            if(skillmap.find(skill_trees[i][j])!=skillmap.end())
            {
                if(skillmap[skill_trees[i][j]]>skillIndx)
                {
                    isCheck=false;
                    break;
                }
                else skillIndx++;    
            }
        }
        if(isCheck)answer++;
    }
    return answer;
}
