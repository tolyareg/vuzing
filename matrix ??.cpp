#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <queue>

#include <math.h>

using namespace std;

class Graph {
    int n;
    bool** gr;
    
public:
    Graph(ifstream& in) {
    // Graph(string& in) {
        in >> n;
        gr = new bool* [n+1];
        
        for (int i = 1; i <= n; ++i) 
        {
            gr[i] = new bool[n+1];
            
            for (int j = 1; j <= n; ++j) 
            {
                in >> gr[i][j];
            }
        }
    }  
    
    bool is_two() {
        int * used = new int [n+1] { 0 };
        int * parent  = new int [n+1] { -1 };
        
        used[1] = 1; // начнем с нее;
        
        queue<int> q;
        q.push(1);
        
        while ( !q.empty() ) 
        {
            int u = q.front();
            q.pop();
            
            for (int i = 1; i <= n; ++i) 
            {
                if (gr[u][i] == 1 && used[i] == 0)  
                {
                    q.push(i);
                    used[i]   = 3 - used[u]; // watafak??
                    // parent[i] = u;
                } 
                else if ( gr[u][i] == 1 && used[i] > 0 ) 
                {
                    if ( used[i] == used[u] )
                        return false;
                        
                } else continue;
            }
        }
        
        return true;
    } 
};

int main() {
    // string in = "4\n0 1 0 1\n1 0 1 0\n0 1 0 1\n1 0 1 0";
    ifstream in(in.txt)
    Graph g(in);
    cout << g.is_two();
    
    return 0;
}

