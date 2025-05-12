#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std;

const int INF = 9999999;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> dp(N + 1, vector<int>(31, INF));

    vector<int> K(N + 1); 

    K[0] = 1;
    dp[0][1] = 0;

    for (int i = 1; i <= N; ++i) {
        cin >> K[i]; 

        for (int j = 1; j <= K[i]; ++j) {
            int p;  
            int cost; 
            
            while (cin >> p && p != 0) {
                cin >> cost;
                if (dp[i - 1][p] != INF) {
                    int potential_cost = dp[i - 1][p] + cost;
                    dp[i][j] = min(dp[i][j], potential_cost);
                }
            }
        }
        
        if (i < N) {
            char separator;
            cin >> separator; 
        }
    } 

    int min_final_cost = INF;
    for (int j = 1; j <= K[N]; ++j)
        min_final_cost = min(min_final_cost, dp[N][j]);

    cout << min_final_cost << endl;

    return 0;
}
