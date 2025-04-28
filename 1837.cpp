#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;

    map<string, vector<string>> graph;
    map<string, int> dist;

    for (int i = 0; i < t; ++i) {
        string a, b, c;
        cin >> a >> b >> c;

        vector<string> team = {a, b, c};

        graph[a].push_back(b);
        graph[a].push_back(c);
        graph[b].push_back(a);
        graph[b].push_back(c);
        graph[c].push_back(a);
        graph[c].push_back(b);
    }

    if (dist.count("Isenbaev")) {
        queue<string> q;
        dist["Isenbaev"] = 0;
        q.push("Isenbaev");

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            int d = dist[cur];
            for (const string& next : graph[cur]) {
                if (dist[next] == -1) {
                    dist[next] = d + 1;
                    q.push(next);
                }
            }
        }
    }

    for (const auto& [name, d] : dist) {
        cout << name << " ";
        if (d == -1) cout << "undefined\n";
        else cout << d << "\n";
    }

    return 0;
}
