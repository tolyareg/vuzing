#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map<string, int> day_to_int = {
    {"Monday", 0}, 
    {"Tuesday", 1}, 
    {"Wednesday", 2},
    {"Thursday", 3}, 
    {"Friday", 4}, 
    {"Saturday", 5}, 
    {"Sunday", 6}
};

vector<string> int_to_day = {
    "Monday", 
    "Tuesday", 
    "Wednesday", 
    "Thursday", 
    "Friday", 
    "Saturday", 
    "Sunday"
};

map<string, int> month_to_index = {
    {"September", 9}, 
    {"October", 10}, 
    {"November", 11}, 
    {"December", 12}
};

int days_in_month(int month) {
    if (month == 9) return 30;
    if (month == 10) return 31;
    if (month == 11) return 30;
    return 24;
}


int days_since_sept1(int month, int day) {
    int total = 0;
    for (int m = 9; m < month; ++m)
        total += days_in_month(m);
    return total + day - 1;
}

int main() {
    string start_day;
    getline(cin, start_day);
    string month;
    int day;
    cin >> month >> day;
    int A, B;
    cin >> A >> B;

    int start_wday = day_to_int[start_day];

    int match_day_index = days_since_sept1(month_to_index[month], day);
    int practice_start = 1; // 2 сентября = 1 день после 1 сентября
    int practice_end = match_day_index - 1;

    if (practice_end < practice_start) {
        cout << "Impossible" << endl;
        return 0;
    }

    int total_days = practice_end - practice_start + 1;

    for (int mask = 1; mask < (1 << 7); ++mask) {
        set<int> practice_days;
        for (int i = 0; i < 7; ++i) {
            if (mask & (1 << i))
                practice_days.insert(i);
        }

        int training_count = 0;
        for (int i = practice_start; i <= practice_end; ++i) {
            int weekday = (start_wday + i) % 7;
            if (practice_days.count(weekday))
                ++training_count;
        }

        if (training_count >= A && training_count <= B) {
            cout << practice_days.size() << endl;
            for (int d : practice_days)
                cout << int_to_day[d] << endl;
            return 0;
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
