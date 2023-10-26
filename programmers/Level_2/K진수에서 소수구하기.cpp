#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(long long number) {
    if (number <= 1) {
        return false; // 1과 1 미만의 수는 소수가 아님
    }
    
    if (number <= 3) {
        return true; // 2와 3은 소수
    }

    if (number % 2 == 0 || number % 3 == 0) {
        return false; // 2 또는 3으로 나누어지는 수는 소수가 아님
    }

    for (long long i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false; // 6k ± 1 형태의 수로 나누어지는 경우는 소수가 아님
        }
    }

    return true; // 위의 조건을 모두 통과하면 소수
}

long long carNumVec(vector<int> numVec)
{
    long long number=0;
    for(int i=0;i<numVec.size();i++)
    {
        number+=numVec[i]*pow(10,i);
    }
    if(!isPrime(number))number=0;
    
    return number;
}

int solution(int n, int k) {
    int answer = 0;
    vector<int> numVec;
    while(true)
    {
        int gaValue = n%k;
        if(gaValue==0)
        {
            if(carNumVec(numVec)!=0) answer++;
            numVec.clear();
        }
        else numVec.push_back(gaValue);
        n/=k;
        if(n<=0)
        {
            if(carNumVec(numVec)!=0) answer++;
            break;
        }
    }
  
    return answer;
}
