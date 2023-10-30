#include <string>
#include <vector>
#include <map>

using namespace std;
vector<string> solution(vector<string> files) {
    vector<string> answer;
    map<string,map<int,vector<int>>> fileMap; // head Num
    //map<pair<string,int>,vector<int>> indexfile; // (head,num) index
    map<int,string> indexTail;          // index tail
    for(int i=0; i<files.size();i++)
    {
        string fileHead;
        int num=0;
        string fileTail;
        bool isHead=true;
        bool isNum=true;
        for(int j=0;j<files[i].size();j++)
        {
            char curChar= files[i][j];
            if(isHead)
            {
                if(curChar>='A'&&curChar<='Z')
                {
                    curChar-=('A'-'a');
                }
                else if(curChar>='0'&&curChar<='9')
                {
                    isHead=false;
                    j--;
                    continue;
                }
                fileHead+=curChar;
            }
            if(!isHead && isNum)
            {
                if(curChar>='0'&&curChar<='9')
                {
                    num*=10;
                    num+=(curChar-'0');
                }
                else
                {
                    isNum=false;
                    continue;
                }
            }
            if(!isHead && !isNum)fileTail.push_back(curChar);
        }
        // map<string,map<int,vector<int>>>
        if(fileMap.find(fileHead)!=fileMap.end())
        {
            auto numMap  = fileMap[fileHead];
            
            fileMap[fileHead][num].push_back(i);
        }
        else
        {
            map<int,vector<int>> dummyMap;
            dummyMap[num].push_back(i);
            fileMap[fileHead] = dummyMap;
        }
        
        indexTail[i]=files[i];
    }
    for(const auto& filePair : fileMap)
    {
        string fileHead = filePair.first;
        for(const auto& numPair:filePair.second)
        {
            int num = numPair.first;
            for(int i=0;i<numPair.second.size();i++)
            {
                int index = numPair.second[i];
                answer.push_back(indexTail[index]);
            }
        }
    }
    return answer;
}
