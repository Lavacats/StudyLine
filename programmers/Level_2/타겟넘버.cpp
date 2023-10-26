#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> numbers, int target) {
    if(numbers.size()==1)
    {
        if(abs(target) == abs(numbers[0]))return 1;
        else return 0;
    }
    int answer = 0;
    sort(numbers.begin(),numbers.end());
    
    int firstValue = numbers[0];
    vector<int> passNumbers;
    for(int i=1;i<numbers.size();i++)passNumbers.push_back(numbers[i]);
 
    answer+=solution(passNumbers, target-firstValue);
    answer+=solution(passNumbers, target+firstValue);
    
    return answer;
}
