#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(vector<vector<string>> book_time) {
    int answer = 0;
    int roomNum=1;
    vector<int> timeBoard;
    for(int i=0;i<=1440;i++)timeBoard.push_back(0);
    for(int i=0;i<book_time.size();i++)
    {
        vector<int> timeLine;
        int sHour = (book_time[i][0][0]-'0')*10+(book_time[i][0][1]-'0');
        int sMin  = (book_time[i][0][3]-'0')*10+(book_time[i][0][4]-'0');
        int eHour = (book_time[i][1][0]-'0')*10+(book_time[i][1][1]-'0');
        int eMin  = (book_time[i][1][3]-'0')*10+(book_time[i][1][4]-'0');
        int startTime = sHour*60+sMin;
        int endTime   = eHour*60+eMin+10; // 청소시간 합산
        for(int i=startTime;i<endTime;i++)
        {
            timeBoard[i]+=1;
            if(answer<timeBoard[i])answer=timeBoard[i];
        }
    }
    return answer;
}
