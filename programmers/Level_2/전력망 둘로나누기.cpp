#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int solution(int n, vector<vector<int>> wires) {
    int answer = (int)wires.size();
    for(int i=0;i<wires.size();i++)sort(wires[i].begin(),wires[i].end());
    sort(wires.begin(),wires.end());
    for(int j=0;j<wires.size();j++)
    {
        map<int,int> map_1;
        vector<vector<int>> dummy;
        dummy=wires;
        int index = (j+1)%dummy.size();
        map_1[dummy[index][0]]=1;
        dummy[index][0]=0;
        map_1[dummy[index][1]]=1;
        dummy[index][1]=0;
        while(true)
        {
            vector<int> list;
            for(const auto& pair: map_1)
            {
                for(int i=0;i<dummy.size();i++)
                {
                    if(i==j)continue;
                    else if(i==index)continue;
                    else
                    {
                        if(dummy[i][0]!=0&&dummy[i][1]!=0)
                        {
                            if(dummy[i][0]==pair.first||dummy[i][1]==pair.first)
                            {
                                list.push_back(wires[i][0]);
                                list.push_back(wires[i][1]);
                                dummy[i][0]=0;
                                dummy[i][1]=0;
                            }
                        }
                    }
                }
            }
            if(list.size()==0)break;
            for(int i=0;i<list.size();i++)map_1[list[i]]=1;
        }
        int left = (n-(int)map_1.size());
        int right =(int)map_1.size();
        if(answer>abs(left-right))answer=abs(left-right);
    }
    return answer;
}
