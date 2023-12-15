#include <string>
#include <vector>

using namespace std;

int solution(int h1, int m1, int s1, int h2, int m2, int s2) {
    int answer = 0;
    int startSeconds = h1 * 3600 + m1 * 60 + s1;
    int endSeconds = h2 * 3600 + m2 * 60 + s2;


    int minutOverap = 0;
    int hourOverap = 0;
    int allOverap = 0;
    bool isCheck_M = true;
    bool isCheck_H = true;
    float prev_S =-1;
    float prev_M =-1;
    float prev_H =-1;

    for (int seconds = startSeconds; seconds <= endSeconds; ++seconds)
    {
        int cur_S = seconds % 60;
        int cur_M = seconds % 3600 / 60;
        int cur_H = seconds % (12 * 3600) / 3600;
        float s_angle = cur_S % 60 * 360 / 60;
        float m_angle = cur_M % 60 * 360 / 60 + cur_S * (360.0 / 60.0 / 60.0);
        float h_angle = cur_H % 12 * 360 / 12 + cur_M * (360.0 / 60.0 / 12.0) + cur_S * (360.0 / 60.0 / 60.0 / 12.0);




        if (s_angle <= m_angle)
        {
            isCheck_M = false;
        }
        if (s_angle <= h_angle)
        {
            isCheck_H = false;
        }
        if (s_angle >= m_angle && !isCheck_M)
        {
            minutOverap++;
            isCheck_M = true;
        }

        if (s_angle >= h_angle && !isCheck_H)
        {
            hourOverap++;
            isCheck_H = true;
        }
        else if (cur_H % 12 == 11)
        {
            if ((cur_M >= 48 && cur_M<59) && cur_S==59)
            {
                if ((seconds + 1) <= endSeconds)
                {
                    hourOverap++;
                    isCheck_H = true;
                }
            }
        }
        if (m_angle == h_angle)allOverap++;

        prev_S = s_angle;
        prev_M = m_angle;
        prev_H = h_angle;
    }
    answer = minutOverap + hourOverap;
    if (answer > allOverap)answer -= allOverap;
    return answer;
}
