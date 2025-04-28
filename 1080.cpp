#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; ++i) {
        int neighbor;
        while (cin >> neighbor && neighbor != 0) {
            graph[i].push_back(neighbor);
            graph[neighbor].push_back(i);
        }
    }

    vector<int> side(n + 1, -1);
    bool ok = true;

    for (int node = 1; node <= n; ++node) {
        if (side[node] == -1) {
            side[node] = 0;
            queue<int> q;
            q.push(node);

            while (!q.empty()) {
                int cur = q.front();
                q.pop();

                for (int next : graph[cur]) {
                    if (side[next] == -1) {
                        side[next] = 1 - side[cur];
                        q.push(next);
                    } else if (side[next] == side[cur]) {
                        ok = false;
                        break;
                    }
                }

                if (!ok) break;
            }
        }

        if (!ok) break;
    }

    if (!ok) {
        cout << -1 << endl;
    } else {
        for (int i = 1; i <= n; ++i) {
            cout << (side[i] == -1 ? 0 : side[i]);
        }
        cout << endl;
    }

    return 0;
}
