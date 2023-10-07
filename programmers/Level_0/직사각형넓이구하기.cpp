#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> dots) {
    int answer = 0;
    int minX=300;
    int maxX=-300;
    int minY=300;
    int maxY=-300;
    for(int i=0; i<dots.size();i++)
    {
        if(dots[i][0]<minX) minX = dots[i][0];
        if(dots[i][0]>maxX) maxX = dots[i][0];
        
        if(dots[i][1]<minY) minY = dots[i][1];
        if(dots[i][1]>maxY) maxY = dots[i][1];
    }
    answer = abs(maxX-minX)*abs(maxY-minY);
    return answer;
}
