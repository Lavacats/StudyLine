#include <string>
#include <vector>
#include <bitset>
using namespace std;

string decimalToBinary(long long decimal) {
    return bitset<64>(decimal).to_string();
}
long long binaryToLongLong(const string& binary) {
    return bitset<64>(binary).to_ullong();
}

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for(int i=0;i<numbers.size();i++)
    {
        if(numbers[i]%2==0)
        {
            answer.push_back(numbers[i]+1);
            continue;
        }
        string bitNum = decimalToBinary(numbers[i]);
        char preNum=bitNum[bitNum.size()-1];
        char curNum='2';
        for(int i=1;i<bitNum.size();i++)
        {
            curNum = bitNum[bitNum.size()-i-1];
            if(preNum=='1'&&curNum=='0')
            {
                bitNum[bitNum.size()-i-1]='1';
                bitNum[bitNum.size()-i]='0';
                break;
            }
            preNum=curNum;
        }
        answer.push_back(binaryToLongLong(bitNum));
    }
    return answer;
}
