#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

bool check(long long min_coolness, int n, int m, const vector<long long>& v_pop, const vector<long long>& h_pop) {
    
    vector<bool> dp_curr(n, false);
    vector<bool> dp_prev(n, false);

    if (v_pop.empty() && h_pop.empty()) return true; 


    dp_prev[0] = true; 
    if (h_pop[0] >= min_coolness) {
        for (int c = 0; c < n; ++c) {
            dp_prev[c] = true;
        }
    }

    if (m == 1) {
        return dp_prev[n-1];
    }

    for (int r = 1; r < m; ++r) {
        dp_curr.assign(n, false); 

        if (dp_prev[0] && (v_pop[0] >= min_coolness)) {
            dp_curr[0] = true;
        }

        bool H_r_usable = (h_pop[r] >= min_coolness);
        for (int c = 1; c < n; ++c) {
            bool can_reach_from_up = dp_prev[c] && (v_pop[c] >= min_coolness);
            bool can_reach_from_left = false;
            if (H_r_usable) {
                can_reach_from_left = dp_curr[c-1];
            }
            dp_curr[c] = can_reach_from_up || can_reach_from_left;
        }
        dp_prev = dp_curr; 
    }

    return dp_prev[n-1]; 
}

bool check_corrected(long long min_coolness, int n, int m, const vector<long long>& v_pop, const vector<long long>& h_pop) {
    vector<bool> dp_row(n, false);

    dp_row[0] = true; 


    if (h_pop[0] >= min_coolness) {
        for (int c = 1; c < n; ++c) {
            dp_row[c] = dp_row[c-1];
        }
    } else { 
        for (int c = 1; c < n; ++c) {
            dp_row[c] = false;
        }
    }


    for (int r = 1; r < m; ++r) {
        if (v_pop[0] >= min_coolness) {
            // dummy
        } else {
            dp_row[0] = false; 
        }
        

        bool H_r_usable = (h_pop[r] >= min_coolness);
        for (int c = 1; c < n; ++c) {

            bool can_reach_from_up = dp_row[c] && (v_pop[c] >= min_coolness);
            bool can_reach_from_left = false;
            if (H_r_usable) {
                can_reach_from_left = dp_row[c-1]; 
            }
            dp_row[c] = can_reach_from_up || can_reach_from_left;
        }
    }
    return dp_row[n-1];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n_vertical_streets, m_horizontal_streets;
    cin >> n_vertical_streets >> m_horizontal_streets;

    vector<long long> v_pop(n_vertical_streets);
    set<long long> distinct_pops;

    for (int i = 0; i < n_vertical_streets; ++i) {
        cin >> v_pop[i];
        distinct_pops.insert(v_pop[i]);
    }

    vector<long long> h_pop(m_horizontal_streets);
    for (int i = 0; i < m_horizontal_streets; ++i) {
        cin >> h_pop[i];
        distinct_pops.insert(h_pop[i]);
    }
    
    long long low = 1, high = 1000000000LL;
    long long ans = 0;

    while(low <= high) {
        long long mid = low + (high - low) / 2;
        if (mid == 0) {
            low = 1;
            continue;
        }
        if (check_corrected(mid, n_vertical_streets, m_horizontal_streets, v_pop, h_pop)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    cout << ans << endl;

    return 0;
}
