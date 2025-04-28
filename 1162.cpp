#include <iostream>
#include <vector>
#include <iomanip> // Для возможного использования setprecision, если нужно выводить double
#include <algorithm> // Для std::max
#include <limits>   // Для numeric_limits (если понадобится -infinity)

// Используем пространство имен std
using namespace std;

// Структура для хранения информации об одном обменном пункте
struct ExchangePoint {
    int a;       // Номер первой валюты
    int b;       // Номер второй валюты
    double rab;  // Курс обмена A на B (сколько B дают за 1 A)
    double cab;  // Комиссия при обмене A на B (взимается в валюте A)
    double rba;  // Курс обмена B на A (сколько A дают за 1 B)
    double cba;  // Комиссия при обмене B на A (взимается в валюте B)
};

int main() {
    // Оптимизация ввода/вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // Количество валют
    int m; // Количество обменных пунктов
    int s; // Стартовая валюта (номер)
    double v; // Начальное количество валюты S

    cin >> n >> m >> s >> v;

    vector<ExchangePoint> points(m);
    for (int i = 0; i < m; ++i) {
        cin >> points[i].a >> points[i].b >> points[i].rab >> points[i].cab >> points[i].rba >> points[i].cba;
    }

    // dist[i] будет хранить максимальное количество валюты i.
    vector<double> dist(n + 1, 0.0); // Инициализируем нулями
    dist[s] = v; // Начальное количество

    // Шаг 1: Выполняем N-1 итераций релаксации
    // Важно: Цикл идет до n, т.к. путь может включать до n ребер (n+1 вершин)
    // Стандартный Беллман-Форд для поиска кратчайших путей делает n-1 итераций.
    // Для поиска циклов достаточно n итераций, если проверять на n+1-й.
    // Давайте попробуем n итераций основного цикла.
    for (int iter = 1; iter <= n; ++iter) { // N итераций релаксации
        bool changed_in_iteration = false; // Флаг изменений на итерации
        for (int j = 0; j < m; ++j) {
            int cur_a = points[j].a;
            int cur_b = points[j].b;
            double cur_rab = points[j].rab;
            double cur_cab = points[j].cab;
            double cur_rba = points[j].rba;
            double cur_cba = points[j].cba;

            // Попытка обмена A -> B
            // Используем небольшую погрешность для сравнения с комиссией
            const double epsilon = 1e-12; // Малое значение для сравнения double
            if (dist[cur_a] >= cur_cab - epsilon) { // Достаточно ли средств A (с учетом погрешности)
                double amount_after_commission_a = dist[cur_a] - cur_cab;
                // Убедимся, что после комиссии не отрицательное число (хотя >= выше должно это гарантировать)
                if (amount_after_commission_a < 0) amount_after_commission_a = 0;
                double potential_b = amount_after_commission_a * cur_rab;

                // Если можем улучшить результат для B (с учетом погрешности)
                if (potential_b > dist[cur_b] + epsilon) {
                    dist[cur_b] = potential_b;
                    changed_in_iteration = true; // Были изменения
                }
            }

            // Попытка обмена B -> A
             if (dist[cur_b] >= cur_cba - epsilon) { // Достаточно ли средств B
                double amount_after_commission_b = dist[cur_b] - cur_cba;
                if (amount_after_commission_b < 0) amount_after_commission_b = 0;
                double potential_a = amount_after_commission_b * cur_rba;

                // Если можем улучшить результат для A
                if (potential_a > dist[cur_a] + epsilon) {
                    dist[cur_a] = potential_a;
                     changed_in_iteration = true; // Были изменения
                }
            }
        }
         // Оптимизация: если на какой-то итерации (до n-й) изменений не было,
         // то и дальше их не будет (если нет положительных циклов).
         // Но для обнаружения цикла нам нужно пройти все n итераций.
         // if (!changed_in_iteration && iter < n) break; // Можно раскомментировать, если не ищем циклы
    }

    // Шаг 2: Проверка на положительный цикл (возможность улучшения на (N+1)-й итерации)
    bool profitable_cycle_found = false;
    for (int j = 0; j < m; ++j) {
         int cur_a = points[j].a;
         int cur_b = points[j].b;
         double cur_rab = points[j].rab;
         double cur_cab = points[j].cab;
         double cur_rba = points[j].rba;
         double cur_cba = points[j].cba;
         const double epsilon = 1e-12; // Та же погрешность

         // Можно ли еще улучшить B через A -> B?
         if (dist[cur_a] >= cur_cab - epsilon) {
             double amount_after_commission_a = dist[cur_a] - cur_cab;
             if (amount_after_commission_a < 0) amount_after_commission_a = 0;
             double potential_b = amount_after_commission_a * cur_rab;
             if (potential_b > dist[cur_b] + epsilon) {
                 profitable_cycle_found = true;
                 break;
             }
         }

         // Можно ли еще улучшить A через B -> A?
         if (dist[cur_b] >= cur_cba - epsilon) {
             double amount_after_commission_b = dist[cur_b] - cur_cba;
             if (amount_after_commission_b < 0) amount_after_commission_b = 0;
             double potential_a = amount_after_commission_b * cur_rba;
             if (potential_a > dist[cur_a] + epsilon) {
                 profitable_cycle_found = true;
                 break;
             }
         }
    }

    // Вывод результата
    if (profitable_cycle_found) {
        cout << "YES" << endl;
    } else {
        // В данном случае цикл не найден, и максимальная достижимая сумма
        // в валюте S после N итераций находится в dist[s].
        // Мы не увеличили капитал, если есть цикл или если dist[s] <= v.
        // Поскольку цикл проверяется отдельно, здесь можно просто вывести NO.
        cout << "NO" << endl;
    }

    return 0;
}
