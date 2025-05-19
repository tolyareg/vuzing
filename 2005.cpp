#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> 

using namespace std;

int main() {
    int D[5][5];

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> D[i][j];
        }
    }

    vector<int> students = {2, 3, 4}; 
    sort(students.begin(), students.end());

    long long min_total_dist = numeric_limits<long long>::max();
    vector<int> optimal_path_points;

    do {
        int s1 = students[0];
        int s2 = students[1];
        int s3 = students[2];

        if (s3 == 3) {
            continue;
        }

        vector<int> current_path_candidate = {1, s1, s2, s3, 5};
        long long current_path_total_dist = 0;


        current_path_total_dist += D[current_path_candidate[0]-1][current_path_candidate[1]-1];
        current_path_total_dist += D[current_path_candidate[1]-1][current_path_candidate[2]-1];
        current_path_total_dist += D[current_path_candidate[2]-1][current_path_candidate[3]-1];
        current_path_total_dist += D[current_path_candidate[3]-1][current_path_candidate[4]-1];
        
        if (current_path_total_dist < min_total_dist) {
            min_total_dist = current_path_total_dist;
            optimal_path_points = current_path_candidate;
        }

    } while (next_permutation(students.begin(), students.end()));

    cout << min_total_dist << endl;

    for (size_t i = 0; i < optimal_path_points.size(); ++i) {
        cout << optimal_path_points[i] << (i == optimal_path_points.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
