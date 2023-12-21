#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int solution(int n, vector<vector<int>> edge) {
    vector<vector<int>> graph(n + 1);

    for (const auto& e : edge) {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<int> distances(n + 1, -1);
    distances[1] = 0;

    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next : graph[current]) {
            if (distances[next] == -1) {
                distances[next] = distances[current] + 1;
                q.push(next);
            }
        }
    }

    int maxDistance = *max_element(distances.begin(), distances.end());
    return count(distances.begin(), distances.end(), maxDistance);
}
