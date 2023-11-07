using namespace std;
int m[1001][1001];
int cnt;

void sol(int x,int y,int sz)
{
    if(sz<=0)
        return;
    if(sz==1)
    {
        m[x][y]=++cnt;
        return;
    }
    for(int i=0;i<sz;i++)
        m[x+i][y]=++cnt;
    for(int i=1;i<sz;i++)
        m[x+sz-1][y+i]=++cnt;
    for(int i=1;i<sz-1;i++)
        m[x+sz-1-i][y+sz-1-i]=++cnt;
    sol(x+2,y+1,sz-3);

}
vector<int> solution(int n) {
    vector<int> answer;
    sol(0,0,n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=i;j++)
            answer.push_back(m[i][j]);
    }

    return answer;
}
