#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n; // количество коробок
    cin >> n;

    vector<pair<int, int>> boxes; // (первый элемент, последний элемент) каждой коробки

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        vector<int> figs(k);
        for (int j = 0; j < k; ++j) {
            cin >> figs[j];
        }

        // Проверяем, что внутри коробки фигурки идут в неубывающем порядке
        for (int j = 1; j < k; ++j) {
            if (figs[j] < figs[j - 1]) {
                cout << "NO" << endl;
                return 0;
            }
        }

        boxes.push_back({figs[0], figs.back()});
    }

    // Сортируем коробки по первому элементу
    sort(boxes.begin(), boxes.end());

    // Проверяем, можно ли соединить коробки в один список с неубывающим порядком
    for (int i = 1; i < n; ++i) {
        if (boxes[i - 1].second > boxes[i].first) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    return 0;
}
