#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;


int formingMagicSquare(vector<vector<int>> s)
{
    vector<vector<vector<int>>> a;
    a = {
        {{8,1,6},{3,5,7},{4,9,2}},
        {{6,1,8},{7,5,3},{2,9,4}},
        {{4,9,2},{3,5,7},{8,1,6}},
        {{2,9,4},{7,5,3},{6,1,8}},
        {{8,3,4},{1,5,9},{6,7,2}},
        {{4,3,8},{9,5,1},{2,7,6}},
        {{6,7,2},{1,5,9},{8,3,4}},
        {{2,7,6},{9,5,1},{4,3,8}},
    };
    int maxMin=1000;
    for(int i=0;i<a.size();i++)
    {
        int minCount=0;
        for(int j=0;j<a[i].size();j++)
        {
            for(int k=0;k<a[i][j].size();k++)
            {
                minCount+=abs(a[i][j][k]-s[j][k]);
            }
        }
        if(maxMin>minCount)maxMin=minCount;
    }
    return maxMin;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    
    vector<vector<int>> s(3);
    s={{4,9,2},{3,5,7},{8,1,5}};
    
    int result = formingMagicSquare(s);
    
   // fout << result << "\n";//
   // fout.close();
    
    return 0;
}

