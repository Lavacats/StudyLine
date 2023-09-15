#include <string>
#include <vector>

using namespace std;

int solution(vector<int> common) {
    int answer = 0;
    size_t vec_Size = common.size();
   
    int num_1 = common[1] - common[0];
    int num_2 = common[2] - common[1];
    
    if(num_1 == num_2)
    {
        answer = common[vec_Size-1]+num_1;
    }
    else
    {
        answer = common[vec_Size-1]*(num_2/num_1);
    }
    
    
    return answer;
}
