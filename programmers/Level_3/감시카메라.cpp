int solution(vector<vector<int>> routes)
{
    int answer = 0;
    sort(routes.begin(), routes.end());

        int standard = routes[0][1];
        int cnt_camera = 1;
        int cnt_car = 0;

        for (int i = 0; i < routes.size(); i++)
        {
            if (standard >= routes[i][0])
            {
                standard = min(routes[i][1], standard);
            }
            else
            {
                cnt_camera += 1;
                standard = routes[i][1];
            }
        }

        answer = cnt_camera;
    return answer;
}
