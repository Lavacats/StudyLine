#include <string>
#include <vector>
#include <map>
using namespace std;

map<string,int> wordMap;
int m_index=0;
void isertWordMap(string word,string total)
{
    if(word.size()>5)return;
    wordMap[word] = m_index;
    m_index++;
    for(int i=0;i<total.size();i++)
    {
        string wordArray = word+total[i];
   
        isertWordMap(wordArray,total);
    }
}

int solution(string word) {
    int answer = 1;
    isertWordMap("","AEIOU");
    answer = wordMap[word];
    return answer;
}
