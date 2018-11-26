#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;

/*
 * Complete the timeConversion function below.
 */
string timeConversion(string s) {
   if(s[s.size()-2]=='P')
   {
       string hour;
       hour.push_back(s[0]);
       hour.push_back(s[1]);
       if(hour!="12")
       {
       int hourIn = atoi(hour.c_str())+12;
       if(hourIn==24)hourIn=0;
       s[0] = (char)(hourIn/10)+'0';
       s[1] = (char)(hourIn%10)+'0';
       }
   }
    if(s[s.size()-2]=='A')
    {
        string hour;
        hour.push_back(s[0]);
        hour.push_back(s[1]);
        if(hour=="12")
        {
            s[0]='0';
            s[1]='0';
        }
    }
    s.pop_back();
    s.pop_back();
    return s;
}

int main()
{
  //  ofstream fout(getenv("OUTPUT_PATH"));
    cout<<"Hey"<<endl;
    string s;
    getline(cin, s);
    
    string result = timeConversion(s);
    int a=0;
    a=10;
   // fout << result << "\n";
    
   // fout.close();
    
    return 0;
}
