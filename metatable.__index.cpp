#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

class Graph {
    int n;
    bool** gr;
public:
    Graph();
    int BFS(int v, int& u);

    void View();
};

int main() {
    Graph gr;
    int v = 1;
    // int d = Bfs(1, v);
    // std::cout << gr.BFS(v, v);

    gr.View();

    return 0;
}

Graph::Graph() {
    int n, m;
    cin >> n >> m;
    int** ar = new int* [n+1];

    for (int i = 1; i <= n; i++) {
        ar[i] = new int[n+1];

        for (int j = 1; j <= m; j++) {
            cin >> ch;
            if (ch == '#') ar[i][j] = 0;
            else ar[i][j] == ++num;
        }
    }

    N = num;
    gr = new bool*[n + 1];

    // матрица смежности
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ver = ar[i][j];
            if (ver > 0) {
                if (ar[i][j + 1] > 0) {
                    gr[ver][ar[i][j+1]] = 1;
                    gr[ar[i][j+1]][ver] = 1;
                }
                if (ar[i+1][j] > 0) {
                    gr[ver][ar[i+1][j]] = 1;
                    gr[ar[i+1][j]][ver] = 1;
                }
            }   
        }
    }
}

void Graph::View() {
    for (int i = 1; i <= n; i++ ) {
        for (int j = 1; i <=n; j++) {
            cout << gr[i][j] << ' ';
        };
    };
    cout << endl;
}

int Graph::BFS(int v1, int& v2) {
    queue<int> q;
    int* dist = new int[N+1]{0};
    bool* used = new bool[N+1]{1};

    q.push(v1);
    used[v1] = 0;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 1; i<=N; i++) {
            if (gr[u][i] == 1 && used[i]) {
                q.push(i);
                used[i] = 0;
                dist[i] = dist[u] +1;

            }
        }
    }

    int index = 1;
    int max_dist = dist[index];

    for (int i = 2; i <= N; i++) {
        if (dist[i] > max_dist) {
            index = i;
            max_dist = dist[i];
        }
    }
    
    v2 = index;
    return max_dist;
    // return max(dist.begin(), dist.end());
}
