
int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    int index=0;
    for (int i = 0; i < n; i++)
    {
        if (index < stations.size() && i >= stations[index] - w)
        {
            i = stations[index] + w;
            index++;
        }
        else
        {
            answer++;
            i += w * 2;
        }
    }
    return answer;
}
