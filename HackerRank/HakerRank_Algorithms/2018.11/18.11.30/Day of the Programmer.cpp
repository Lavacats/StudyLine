#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

// Complete the dayOfProgrammer function below.
string dayOfProgrammer(int year) {
    if(year<1918){
        if(year%4==0){
            string frontLine="12.09";
            string secondLine = to_string(year);
            return frontLine+secondLine;
        }
        else{
            string frontLine="13.09";
            string secondLine = to_string(year);
            return frontLine+secondLine;
        }
    }
    else if(year==1918)
    {
        string frontLine="26.09";   // 그레고리와 율리우스 차이만큼
        string secondLine = to_string(year);
        return frontLine+secondLine;
    }
    else
    {
        if(year%4==0 && year %100!=0)
        {
        string frontLine="12.09";
        string secondLine = to_string(year);
        return frontLine+secondLine;
        }
        else{
        string frontLine="13.09";
        string secondLine = to_string(year);
        return frontLine+secondLine;
        }
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
    
    string year_temp;
    getline(cin, year_temp);
    
    int year = stoi(ltrim(rtrim(year_temp)));
    
    string result = dayOfProgrammer(year);
    
    fout << result << "\n";
    
    fout.close();
    
    return 0;
}

string ltrim(const string &str) {
    string s(str);
    
    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
            );
    
    return s;
}

string rtrim(const string &str) {
    string s(str);
    
    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
            );
    
    return s;
}
