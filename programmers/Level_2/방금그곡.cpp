#include <string>
#include <vector>
#include <sstream>
using namespace std;

int getTime(string& s, string& e) {// 라디오에 플레이된 시간 계산
    int s_time = stoi(s) * 60 + stoi(s.substr(3));
    int e_time = stoi(e) * 60 + stoi(e.substr(3));
    return e_time - s_time;
}

bool isSame(string& m, string& tmp) {// 노래를 찾았는지 판별
    // "ABC" "ABC#" 와 같은 예시는 같은 음이 아니기 때문에 유의해야한다.
    int m_size = m.size(), tmp_size = tmp.size(), idx;
    for (int i=0; i<m_size; i++) {
        if ((idx = m.find(tmp, i)) != -1 && m[idx+tmp_size] != '#') return true;
    }
    for (int i=0; i<tmp_size; i++) {
        if ((idx = tmp.find(m, i)) != -1 && tmp[idx+m_size] != '#') return true;
    }
    return false;
}

string solution(string m, vector<string> musicinfos) {
    string answer = "(None)";
    int time = 0;
    for (auto infos : musicinfos) {
        istringstream iss(infos);
        vector<string> data;
        string tmp;
        while (getline(iss, tmp, ',')) {// ','을 기준이로 나누어서 저장
            data.push_back(tmp);
        }
        int played_time = getTime(data[0], data[1]);
        if (played_time <= time) continue;// 어차피 실제 플레이 시간이 조건에 맞는 곡의 곡 시간보다 길어야 하기 떄문에
        int music_time = 0;
        for (auto c : data[3]) if (c != '#') music_time++;// 악보에 따른 음악시간 측정, size()로 하면 안됨
        int tmp_time = music_time;
        
        while (tmp_time < played_time) {//라디오 플레이시간보다 길때까지 반복 재생
            tmp += data[3];
            tmp_time += music_time;
        }
        
        while (tmp_time > played_time) {//라디오 플레이시간에 맞게 잘라준다.
            if (tmp.back() == '#') tmp.pop_back();
            tmp.pop_back();
            tmp_time--;
        }
        
        if (isSame(m, tmp)) {// 조건에 맞다면
            answer = data[2];
            time = played_time;
        }
    }
    return answer;
}
