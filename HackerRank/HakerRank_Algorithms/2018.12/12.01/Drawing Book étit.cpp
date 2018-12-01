#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

/*
 * Complete the pageCount function below.
 */
int pageCount(int n, int p) {
    vector<int> arr;
    for(int i=0; i<n+1;i++)arr.push_back(i);

    int frontCount=0;
    for(int i=0; i<arr.size();i+=2)
    {
        if(p ==arr[i] || p==arr[i]+1)
        {
            break;
        }
        else
        {
            frontCount++;
        }
    }
    int backCount=0;
    for(int i=arr.size()-1; i>=0;i-=2)
    {
        if(n%2==1)
        {
            if(p ==arr[i] || p==arr[i]-1)
            {
                break;
            }
            else
            {
                backCount++;
            }
        }
        else{
            if(p ==arr[i] || p==arr[i]+1)
            {
                break;
            }
            else
            {
                backCount++;
            }
        }
    }
    return (frontCount<backCount)? frontCount : backCount;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    
    int n;
    cout<<"hey";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    int p;
    cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    int result = pageCount(n, p);
    int a=0;
    //fout << result << "\n";
    
    //fout.close();
    
    return 0;
}
