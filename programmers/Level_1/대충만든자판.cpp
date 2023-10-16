#include <string>
#include <vector>

using namespace std;

int ComboKey(char key, string keyBoard)
{
    int count=0;
    for(int i=0;i<keyBoard.size();i++)
    {
        count++;
        if(keyBoard[i]==key)break;
        if(i==keyBoard.size()-1)count=-1;
    }
    return count;
}


vector<int> solution(vector<string> keymap, vector<string> targets) {
    vector<int> answer;
    
    // 문자열 순회
    for(int i=0; i<targets.size();i++)
    {
        int comboKeyBoard = 0;
        // 문자 순회
        for(int k=0;k<targets[i].size();k++)
        {
            int minValue=200;
            // 키로 누를수 있는 최소 값 확인
            for(int j=0;j<keymap.size();j++)
            {
                int countKey =ComboKey(targets[i][k],keymap[j]);
                if(countKey<minValue && countKey>0)minValue=countKey;
            }
            
            if(minValue==200)
            {
                comboKeyBoard=-1;
                break;
            }
            else
            {
                comboKeyBoard+=minValue;
            }
        }
        
        answer.push_back(comboKeyBoard);
    }
    return answer;
}
