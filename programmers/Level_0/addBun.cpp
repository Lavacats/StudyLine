#include <string>
#include <vector>

using namespace std;

int gcdcur(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

vector<int> solution(int numer1, int denom1, int numer2, int denom2) {
    vector<int> answer;
    
    int m_numer1 = numer1*denom2;
    int m_denom1 = denom1*denom2;
    int m_numer2 = numer2*denom1;
    int m_denom2 = denom1*denom1;
    
    int ant_1 = m_numer1+m_numer2;
    int ant_2 = denom1*denom2;
    
    int m_gcp=gcdcur(ant_1,ant_2);
    
    ant_1/=m_gcp;
    ant_2/=m_gcp;
    
    answer.emplace_back(ant_1);
    answer.emplace_back(ant_2);
    
    return answer;
}
