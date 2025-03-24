#include <iostream>

using namespace std;

class Graph {
public:
    int n, m, q;
    
    int edges_u[100], edges_v[100];
    int removed_edges[100];
    
    bool adj[100][100];
    bool visited[100];

    Graph(int nodes, int edges);
    
    void ReadEdges();
    void ReadRemovedEdges();
    
    void View();
    
    void InitializeGraph();
    void BuildGraph(int removed_count);
    
    void BFS(int node);
    
    int CountComponents();
};

Graph::Graph(int nodes, int edges) : n(nodes), m(edges) {}

int main() {
    int n, m;
    cin >> n >> m;
    
    Graph gr(n, m);
    gr.ReadEdges();
    gr.ReadRemovedEdges();
    gr.View();
    
    return 0;
}

void Graph::ReadEdges() {
    if (m > 100) 
        return;
        
    for (int i = 0; i < m; ++i) {
        cin >> edges_u[i] >> edges_v[i];
    }
}

void Graph::ReadRemovedEdges() {
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> removed_edges[i];
    }
}

void Graph::View() {
    for (int i = 0; i < q; ++i) {
        BuildGraph(i + 1);
        cout << CountComponents() << ' ';
    }
}

void Graph::InitializeGraph() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adj[i][j] = false;
        }
        visited[i] = false;
    }
}

void Graph::BuildGraph(int removed_count) {
    if (q > 100) 
        return;
        
    InitializeGraph();
    for (int i = 0; i < m; ++i) {
        bool removed = false;
        for (int j = 0; j < removed_count; ++j) {
            if (removed_edges[j] == i + 1) {
                removed = true;
                break;
            }
        }
        if (!removed) {
            int u = edges_u[i] - 1;
            int v = edges_v[i] - 1;
            adj[u][v] = adj[v][u] = true;
        }
    }
}

void Graph::BFS(int node) {
    if (node < 0 || node >= n) 
        return;
        
    visited[node] = true;
    for (int i = 0; i < n; ++i) {
        if (adj[node][i] && !visited[i]) {
            BFS(i);
        }
    }
}

int Graph::CountComponents() {

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            BFS(i);
            count++;
        }
    }
    return count;
}
