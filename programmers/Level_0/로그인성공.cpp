#include <string>
#include <vector>

using namespace std;

string solution(vector<string> id_pw, vector<vector<string>> db) {
    string answer = "fail";
    string m_ID = id_pw[0];
    string m_PW = id_pw[1];
    for(int i=0; i<db.size();i++)
    {
        if(0==m_ID.compare(db[i][0]))
        {
            answer = "wrong pw";
            if(0==m_PW.compare(db[i][1]))
            {
                answer = "login";
                return answer;
            }
        }
    }
    return answer;
}
