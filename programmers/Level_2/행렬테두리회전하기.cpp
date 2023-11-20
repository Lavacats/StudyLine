#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    vector<vector<int>> mapValue;
    int m_index=1;
    for(int i=0;i<rows;i++)
    {
        vector<int> numVec;
        for(int j=1;j<=columns;j++)
        {
            numVec.push_back(m_index);
            m_index++;
        }
        mapValue.push_back(numVec);
    }
    for(int j=0;j<queries.size();j++)
    {
        int leftPointY = queries[j][0]-1;
        int leftPointX = queries[j][1]-1;
        int rightPointY = queries[j][2]-1;
        int rightPointX = queries[j][3]-1;
        vector<int> numVec;
        int curValue=mapValue[leftPointX][leftPointY];
        int preValue =0;
        
        preValue = mapValue[leftPointY][leftPointX];
        numVec.push_back(preValue);
        for(int i=1;i<=(rightPointX-leftPointX);i++)
        {
            curValue = mapValue[leftPointY][leftPointX+i];
            mapValue[leftPointY][leftPointX+i] = preValue;
            preValue=curValue;
            numVec.push_back(preValue);
        }
        for(int i=1;i<=(rightPointY-leftPointY);i++)
        {
            curValue =  mapValue[leftPointY+i][rightPointX];
            mapValue[leftPointY+i][rightPointX] = preValue;
            preValue=curValue;
            numVec.push_back(preValue);
        }
        for(int i=1;i<=(rightPointX-leftPointX);i++)
        {
            curValue = mapValue[rightPointY][rightPointX-i];
            mapValue[rightPointY][rightPointX-i]= preValue;
            preValue=curValue;
            numVec.push_back(preValue);
        }
        for(int i=1;i<=(rightPointY-leftPointY);i++)
        {
            curValue =  mapValue[rightPointY-i][leftPointX];
            mapValue[rightPointY-i][leftPointX] = preValue;
            preValue=curValue;
            numVec.push_back(preValue);
        }
        sort(numVec.begin(),numVec.end());
        answer.push_back(numVec[0]);
    }
    return answer;
}
