#include <string>
#include <vector>
#include <map>
using namespace std;
int solution(vector<int> elements) {
    int answer = 0;
    map<int,int> elementMap;

    for(int i=0;i<elements.size();i++)
    {
        if(elementMap.find(elements[i])==elementMap.end())elementMap[elements[i]]=1;
    }
    for(int i=0;i<elements.size();i++)
    {
        int firstNum = elements[i];
        int secondNum = 0;
        for(int j=1;j<elements.size();j++)
        {
            int index=i+j;
            if(index>=(int)elements.size())index%=(int)elements.size();
            secondNum+=elements[index];
            
            if(elementMap.find(firstNum+secondNum)==elementMap.end())elementMap[firstNum+secondNum]=1;
        }
    }
    answer=elementMap.size();

    return answer;
}
