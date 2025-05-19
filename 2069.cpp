#include <iostream>
#include <vector>
#include <algorithm>
#include <set> 

using namespace std;

// Структура для узла дерева отрезков
struct Node {
    bool exists_good_h; // True, если в диапазоне узла есть H[i] >= X_threshold
    int max_idx_good_h; // Максимальный индекс i такой, что H[i] >= X_threshold, или -1
};

vector<Node> tree_seg; // Вектор для хранения дерева отрезков
const vector<int>* H_ptr_global_seg; // Указатель на массив популярностей горизонтальных улиц

// Рекурсивная функция построения дерева отрезков
void build_seg_tree_recursive(int node_idx, int L, int R, int X_threshold) {
    if (L == R) { // Листовой узел
        if ((*H_ptr_global_seg)[L] >= X_threshold) {
            tree_seg[node_idx] = {true, L};
        } else {
            tree_seg[node_idx] = {false, -1};
        }
        return;
    }
    int mid = L + (R - L) / 2; // Середина диапазона
    build_seg_tree_recursive(2 * node_idx, L, mid, X_threshold); // Строим левое поддерево
    build_seg_tree_recursive(2 * node_idx + 1, mid + 1, R, X_threshold); // Строим правое поддерево

    // Объединяем информацию от дочерних узлов
    Node left_child = tree_seg[2 * node_idx];
    Node right_child = tree_seg[2 * node_idx + 1];
    tree_seg[node_idx].exists_good_h = left_child.exists_good_h || right_child.exists_good_h;
    tree_seg[node_idx].max_idx_good_h = max(left_child.max_idx_good_h, right_child.max_idx_good_h);
}

// Рекурсивная функция запроса к дереву отрезков
Node query_seg_tree_recursive(int node_idx, int currentL, int currentR, int queryL, int queryR) {
    // Если диапазон запроса пуст или не пересекается с текущим узлом
    if (queryL > queryR || queryL > currentR || queryR < currentL) { 
        return {false, -1};
    }

    // Если текущий узел полностью внутри диапазона запроса
    if (queryL <= currentL && currentR <= queryR) { 
        return tree_seg[node_idx];
    }

    int mid = currentL + (currentR - currentL) / 2;
    Node res_left = query_seg_tree_recursive(2 * node_idx, currentL, mid, queryL, queryR);
    Node res_right = query_seg_tree_recursive(2 * node_idx + 1, mid + 1, currentR, queryL, queryR);

    // Объединяем результаты от дочерних узлов
    return {res_left.exists_good_h || res_right.exists_good_h,
            max(res_left.max_idx_good_h, res_right.max_idx_good_h)};
}

// Функция проверки, можно ли достичь конца с минимальной крутостью X_threshold
bool can_reach_end(int X_threshold, int n, int m, const vector<int>& V, const vector<int>& H) {
    H_ptr_global_seg = &H; // Устанавливаем глобальный указатель на H

    // Constraints: n, m >= 2. Так что m > 0 гарантировано.
    tree_seg.assign(4 * m, {false, -1}); // Инициализируем дерево отрезков
    build_seg_tree_recursive(1, 0, m - 1, X_threshold); // Строим дерево для текущего X_threshold
    
    vector<int> dp_max_row(n, -1); // dp_max_row[c] = максимальный ряд r, достижимый на улице V[c]

    // Базовый случай: первая вертикальная улица (c=0)
    if (V[0] >= X_threshold) {
        dp_max_row[0] = m - 1; // Можно достичь (0, m-1) по V[0]
    } else {
        dp_max_row[0] = 0;     // Можно достичь только (0,0) (нельзя двигаться вниз по V[0])
    }

    // Динамическое программирование по вертикальным улицам (колонкам)
    for (int c = 0; c < n - 1; ++c) {
        if (dp_max_row[c] == -1) { // Если текущая улица V[c] недостижима
            continue;
        }

        int max_r_accessible_on_V_c = dp_max_row[c]; // Макс. ряд, доступный на V[c]
        
        // Запрос к дереву отрезков: ищем "хорошие" H-улицы в диапазоне [0, max_r_accessible_on_V_c]
        Node h_query_result = query_seg_tree_recursive(1, 0, m - 1, 0, max_r_accessible_on_V_c);

        if (!h_query_result.exists_good_h) { // Если нет подходящей H-улицы для перехода
            continue; // dp_max_row[c+1] останется -1
        }

        // Если переход на V[c+1] возможен
        if (V[c+1] >= X_threshold) { // Если по V[c+1] можно двигаться вниз
            dp_max_row[c+1] = m - 1; // Можно достичь (c+1, m-1)
