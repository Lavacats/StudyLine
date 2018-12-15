#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
#include<sstream>
using namespace std;


vector<string> split_string(string);

int beautifulDays(int i, int j, int k) {
    int count=0;
    for(int a=i;a<=j;a++)
    {
        int reverseNum=0;
        int dummy=a;
        while(dummy)
        {
            reverseNum = (reverseNum*10)+(dummy%10);
            dummy=dummy/10;
        }
        float answer = (abs(a-reverseNum)/(float)k);
        if(answer-(int)answer==0)count++;
    }
    return count;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    
    //string ijk_temp;
    //getline(cin, ijk_temp);
    
    //vector<string> ijk = split_string(ijk_temp);
    
    int i = 20;
    
    int j = 23;
    
    int k = 6;
    
    int result = beautifulDays(i, j, k);
    
   // fout << result << "\n";
    
   // fout.close();
    
    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });
    
    input_string.erase(new_end, input_string.end());
    
    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }
    
    vector<string> splits;
    char delimiter = ' ';
    
    size_t i = 0;
    size_t pos = input_string.find(delimiter);
    
    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));
        
        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
    
    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));
    
    return splits;
}
