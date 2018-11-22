#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    cout<<"hey"<<endl;
    int N,S,P,Q;
    cin>>N>>S>>P>>Q;
    vector<int> answer(N);
    
    answer[0] = (S % (1<<31));
    for(int i=1;i<N;i++)
    {
        answer[i]=((answer[i-1]*P+Q) % (1<<31));
    }
    
    bool sameValue=false;
    
    for(int i=(N-1); i>0;i++)
    {
        if(answer[i]==answer[i-1])
        {
            sameValue=true;
            break;
        }
    }
    
    
    if(!sameValue)cout<<N<<endl;
    else
    {
        int numCount=0;
        for(int i=0; i<answer.size();i++)
        {
            if(answer[i]!=answer[i+1])numCount++;
            else break;
        }
        cout<<numCount<<endl;
    }
    return 0;
}
