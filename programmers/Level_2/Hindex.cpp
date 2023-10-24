#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> citations) {
	int answer = 0;
	sort(citations.begin(), citations.end());
    int maxH = citations[citations.size()-1];
    int minH = 0;
	for (int i = maxH; i >= minH; i--)
	{
		for(int j=0;j<citations.size();j++)
        {
            if(citations[j]>=i)
            {
                if(i>=j&&i<=((int)citations.size()-j))
                {
                    if(i>answer)answer=i;
                }
                break;
            }
        }
	}
	return answer;
}
