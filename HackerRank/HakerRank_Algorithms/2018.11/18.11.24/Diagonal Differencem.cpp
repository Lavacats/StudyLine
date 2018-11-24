#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;

// Complete the diagonalDifference function below.
int diagonalDifference(vector<vector<int>> arr) {
    int firstNum=0;
    int secondNum=0;
    for(int i=0; i<arr.size();i++)
    {
        for(int j=0;j<arr[i].size();j++)
        {
            if(i==j)firstNum+=arr[i][j];
            if((arr[i].size()-1-i)==j)
            {
                secondNum+=arr[i][j];
            }
        }
    }
    return abs(firstNum-secondNum);
}

int main()
{
    cout<<"hey"<<endl;
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    vector<vector<int>> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].resize(n);
        
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    int result = diagonalDifference(arr);
    
  
    
    return 0;
}
