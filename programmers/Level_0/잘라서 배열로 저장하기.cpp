#include <string>
#include <vector>

using namespace std;

vector<string> solution(string my_str, int n) {
    vector<string> answer;
    string dummy;
    for(int i=0; i<my_str.size();i++)
    {
        dummy.push_back(my_str[i]);
        if(((i+1)%n==0) || (i+1)==my_str.size())
        {
            answer.push_back(dummy);
            dummy = "";
        }
    }
    return answer;
}
