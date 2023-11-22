#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int GCD(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
void Factors(int N , vector<int>& num_gcd)
{
    for (int i = 1; i <= N; ++i)
    {
        if (N % i == 0) num_gcd.push_back(i);
    }
}
int solution(vector<int> arrayA, vector<int> arrayB) {
    int answer = 0;
    int a_gcd=arrayA[0];
    vector<int> vec_aGcd;
    int b_gcd=arrayB[0];
    vector<int> vec_bGcd;
    for(int i=1;i<arrayA.size();i++)a_gcd=GCD(a_gcd,arrayA[i]);
    for(int i=1;i<arrayB.size();i++)b_gcd=GCD(b_gcd,arrayB[i]);
    Factors(a_gcd, vec_aGcd);
    Factors(b_gcd, vec_bGcd);
    vector<int> vec_solution;

    for(int j=0;j<vec_bGcd.size();j++)
    {
        bool isCheck=true;
        for(int i=0;i<arrayA.size();i++)
        {
            if((arrayA[i]%vec_bGcd[j])==0)
            {
                isCheck=false;
                break;
            }
        }
        if(isCheck)vec_solution.push_back(vec_bGcd[j]);
    }
    for(int j=0;j<vec_aGcd.size();j++)
    {
        bool isCheck=true;
        for(int i=0;i<arrayB.size();i++)
        {
            if((arrayB[i]%vec_aGcd[j])==0)
            {
                isCheck=false;
                break;
            }
        }
        if(isCheck)vec_solution.push_back(vec_aGcd[j]);
    }
    sort(vec_solution.begin(),vec_solution.end());
     if(vec_solution.size()!=0)answer=vec_solution[vec_solution.size()-1];
    return answer;
}
