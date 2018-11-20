#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct WorkShop
{
    int StartTime;
    int duration;
    int endTime;
};

struct Available_Workshops
{
    int num;
    vector<WorkShop> vectorWork;
    Available_Workshops(int n)           // stuct에서의 생성자
    {
        vectorWork = vector<WorkShop>(n);
        num=n;
    }
};
bool compare(WorkShop &a, WorkShop &b)  // i 번째 workshop의 endtime와 i+1 endtime을 비교
{
    return (a.endTime)< (b.endTime);
}

Available_Workshops* initialize (int start_time[], int duration[], int n)
{
    Available_Workshops * ans = new Available_Workshops(n);
    for(int i = 0; i < n; i++)
    {
        ans->vectorWork[i].StartTime = start_time[i];
        ans->vectorWork[i].duration = duration[i];
        ans->vectorWork[i].endTime = start_time[i]+duration[i];
    }
    sort(ans->vectorWork.begin(),ans->vectorWork.end(),compare);
    return ans;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    int count =0;
    int endtime = 0;
    for(int i=0; i<ptr->num;i++)
    {
        if(ptr->vectorWork[i].StartTime >= endtime)
        {
            endtime = ptr->vectorWork[i].StartTime+ptr->vectorWork[i].duration;
            count++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    int n; // number of workshopsㅋ
    cout<<"hey"<<endl;
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];
    
    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }
    
    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
