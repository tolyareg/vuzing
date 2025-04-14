#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

map<int, map<int, int>> graph;
map<int, int> deg_in, deg_out;
set<int> all_nodes;
vector<int> path;
stack<int> s;

int main() {
    int route_count;
    cin >> route_count;

    int edge_total = 0;
    int first_node = -1;

    for (int i = 0; i < route_count; ++i) {
        int stops;
        cin >> stops;

        if (stops < 1) {
            if (stops == 1) {
                int a, b;
                cin >> a >> b;
                all_nodes.insert(a);
                if (first_node == -1) first_node = a;
            }
            continue;
        }

        vector<int> seq(stops + 1);
        for (int j = 0; j <= stops; ++j) {
            cin >> seq[j];
            all_nodes.insert(seq[j]);
        }

        if (first_node == -1) {
            first_node = seq[0];
        }

        for (int j = 0; j < stops; ++j) {
            int from = seq[j];
            int to = seq[j + 1];
            graph[from][to]++;
            deg_out[from]++;
            deg_in[to]++;
            edge_total++;
        }
    }

    bool ok = true;
    if (edge_total > 0) {
        for (int v : all_nodes) {
            int in_d = deg_in.count(v) ? deg_in[v] : 0;
            int out_d = deg_out.count(v) ? deg_out[v] : 0;
            if (in_d != out_d) {
                ok = false;
                break;
            }
        }
    }

    if (!ok || edge_total == 0) {
        cout << 0 << endl;
        return 0;
    }

    int start = -1;
    if (first_node != -1 && deg_out.count(first_node) && deg_out[first_node] > 0) {
        start = first_node;
    } else {
        for (int v : all_nodes) {
            if (deg_out.count(v) && deg_out[v] > 0) {
                start = v;
                break;
            }
        }
    }

    if (start == -1) {
        cout << 0 << endl;
        return 0;
    }

    s.push(start);

    while (!s.empty()) {
        int v = s.top();
        bool moved = false;

        if (graph.count(v) && deg_out[v] > 0) {
            auto& nexts = graph[v];
            for (auto it = nexts.begin(); it != nexts.end(); ++it) {
                if (it->second > 0) {
                    int u = it->first;
                    it->second--;
                    deg_out[v]--;
                    s.push(u);
                    moved = true;
                    break;
                }
            }
        }

        if (!moved) {
            path.push_back(v);
            s.pop();
        }
    }

    reverse(path.begin(), path.end());

    if (path.empty() || path.size() - 1 != edge_total) {
        cout << 0 << endl;
    } else {
        cout << path.size() - 1 << " ";
        for (int x : path) cout << x << " ";
        cout << endl;
    }

    return 0;
}
