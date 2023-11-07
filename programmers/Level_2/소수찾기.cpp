#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
bool isPrime(int number) {
    if (number <= 1) {
        return false;  // 1 이하의 숫자는 소수가 아닙니다.
    }
    if (number <= 3) {
        return true;   // 2와 3은 소수입니다.
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false;  // 2 또는 3의 배수는 소수가 아닙니다.
    }

    // 5부터 시작하여 6씩 증가하며 소수를 판별합니다.
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

int solution(string numbers) {
    int answer=0;
    vector<int> possibleNumber;
    map<int,int> checkMap;
    sort(numbers.begin(), numbers.end());
      do {
          for (int i = 0; i < numbers.size(); i++)
          {
              int value =stoi(numbers.substr(0, i + 1));
              if(checkMap.find(value)==checkMap.end())
              {
                  checkMap[value]=1;
                  possibleNumber.push_back(value);
              }
          }
      } while (next_permutation(numbers.begin(), numbers.end()));
    sort(possibleNumber.begin(), possibleNumber.end());
    
    for (int i = 0; i < possibleNumber.size(); i++)
      {
          if (isPrime(possibleNumber[i]))
              answer++;
      }
    return answer;
}
