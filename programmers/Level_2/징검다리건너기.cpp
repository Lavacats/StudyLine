#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 0;
    int left = 1;
    int right = *max_element(stones.begin(), stones.end());

    while (left <= right) {
        int mid = (left + right) / 2; // mid번까지 건널 수 있도록 설정

        int cnt = 0; // 현재 설정한 mid로 건널 수 있는 인원 수
        int maxZeroCnt = 0; // 연속된 0의 최대 개수

        for (int i = 0; i < stones.size(); ++i) {
            if (stones[i] < mid) {
                cnt++;
                maxZeroCnt = max(maxZeroCnt, cnt);
            }
            else {
                cnt = 0;
            }
        }

        if (maxZeroCnt >= k) {
            // mid번까지 건널 수 없는 경우
            right = mid - 1;
        }
        else {
            // mid번까지 건널 수 있는 경우
            left = mid + 1;
            answer = mid; // 현재 설정한 mid로 건널 수 있는 인원 수를 저장
        }
    }

    return answer;
}
