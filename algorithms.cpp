#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <array>
#include <algorithm> // ОСНОВНОЙ ХЕДЕР С АЛГОРИТМАМИ
#include <numeric>   // Для accumulate, iota, inner_product, partial_sum
#include <iterator>  // Для ostream_iterator, back_inserter
#include <random>  
#include <functional> // Иногда нужно для function<> или bind, но чаще лямбды рулят

// Вспомогательная функция для печати контейнеров (чтобы не повторяться)
template <typename Container>
void printContainer(const Container& c, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    std::cout << "[";
    bool first = true;
    for (const auto& elem : c) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << elem;
        first = false;
    }
    std::cout << "]" << std::endl;
}

// Вспомогательная функция для печати диапазона по итераторам
template <typename Iter>
void printRange(Iter begin, Iter end, const std::string& label = "") {
     if (!label.empty()) {
        std::cout << label << ": ";
    }
    std::cout << "[";
    bool first = true;
    for (Iter it = begin; it != end; ++it) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << *it;
        first = false;
    }
    std::cout << "]" << std::endl;
}


int main() {
    // --- Подготовка данных ---
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    const std::vector<int> original_v = v; // Сохраним оригинал для сброса
    std::string s = "hello world";
    std::list<int> l = {100, 200, 300};
    std::array<int, 4> arr = {7, 8, 9, 10};
    std::vector<int> dest; // Пустой вектор для результатов копирования/трансформации

    std::cout << "--- ИСХОДНЫЕ ДАННЫЕ ---" << std::endl;
    printContainer(v, "Вектор v");
    printContainer(s, "Строка s");
    printContainer(l, "Список l");
    printContainer(arr, "Массив arr");
    std::cout << "\n";


    // === 1. НЕИЗМЕНЯЮЩИЕ АЛГОРИТМЫ ===
    std::cout << "=== 1. НЕИЗМЕНЯЮЩИЕ АЛГОРИТМЫ ===" << std::endl;

    // find: найти первое вхождение '1'
    auto it_find = std::find(v.begin(), v.end(), 1);
    if (it_find != v.end()) {
        std::cout << "find(1): Найдено на позиции " << std::distance(v.begin(), it_find) << std::endl;
    }

    // find_if: найти первое четное число
    auto it_find_if = std::find_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    if (it_find_if != v.end()) {
        std::cout << "find_if(четное): Найдено значение " << *it_find_if << std::endl;
    }

    // count: посчитать количество '5'
    int count_5 = std::count(v.begin(), v.end(), 5);
    std::cout << "count(5): " << count_5 << std::endl;

    // count_if: посчитать числа > 3
    int count_gt3 = std::count_if(v.begin(), v.end(), [](int x){ return x > 3; });
    std::cout << "count_if(>3): " << count_gt3 << std::endl;

    // search: найти подпоследовательность {4, 1, 5}
    std::vector<int> sub = {4, 1, 5};
    auto it_search = std::search(v.begin(), v.end(), sub.begin(), sub.end());
    if (it_search != v.end()) {
         std::cout << "search({4, 1, 5}): Найдено на позиции " << std::distance(v.begin(), it_search) << std::endl;
    }

    // equal: сравнить начало v с {3, 1, 4}
    std::vector<int> prefix = {3, 1, 4};
    bool are_equal = std::equal(prefix.begin(), prefix.end(), v.begin());
    std::cout << "equal(v начало, {3, 1, 4}): " << std::boolalpha << are_equal << std::endl;

    // mismatch: найти первую пару несовпадающих элементов v и {3, 1, 99, ...}
    std::vector<int> v_diff = {3, 1, 99, 1, 5};
    auto pair_mismatch = std::mismatch(v.begin(), v.end(), v_diff.begin());
    if (pair_mismatch.first != v.end()) {
        std::cout << "mismatch(v, v_diff): Первое расхождение " << *pair_mismatch.first << " vs " << *pair_mismatch.second << std::endl;
    }

    // for_each: применить лямбду (печать квадрата) к каждому элементу
    std::cout << "for_each(печать квадратов): ";
    std::for_each(v.begin(), v.end(), [](int x){ std::cout << x*x << " "; });
    std::cout << std::endl;

    // all_of, any_of, none_of: проверки условий
    bool all_positive = std::all_of(v.begin(), v.end(), [](int x){ return x > 0; });
    bool any_even = std::any_of(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    bool none_zero = std::none_of(v.begin(), v.end(), [](int x){ return x == 0; });
    std::cout << "all_of(>0): " << all_positive << ", any_of(четное): " << any_even << ", none_of(==0): " << none_zero << std::endl;
    std::cout << "\n";


    // === 2. ИЗМЕНЯЮЩИЕ АЛГОРИТМЫ ===
    std::cout << "=== 2. ИЗМЕНЯЮЩИЕ АЛГОРИТМЫ ===" << std::endl;
    v = original_v; // Сброс v
    dest.clear();
    dest.resize(v.size()); // Подготовим место в dest

    // copy: скопировать v в dest
    std::copy(v.begin(), v.end(), dest.begin());
    printContainer(dest, "copy(v -> dest)");

    // copy_if: скопировать нечетные из v в dest_if (используем back_inserter)
    std::vector<int> dest_if;
    std::copy_if(v.begin(), v.end(), std::back_inserter(dest_if), [](int x){ return x % 2 != 0; });
    printContainer(dest_if, "copy_if(нечетные)");

    // move: переместить первые 3 элемента v в начало dest (v изменится!)
    std::move(v.begin(), v.begin() + 3, dest.begin());
    printContainer(dest, "move(v[0..2] -> dest)");
    printContainer(v, "v после move"); // Элементы v[0..2] в неопределенном состоянии

    // transform: записать в dest квадраты элементов v
    v = original_v; // Сброс v
    dest.resize(v.size());
    std::transform(v.begin(), v.end(), dest.begin(), [](int x){ return x * x; });
    printContainer(dest, "transform(v -> v*v в dest)");
    // transform на месте: увеличить каждый элемент v на 10
    std::transform(v.begin(), v.end(), v.begin(), [](int x){ return x + 10; });
    printContainer(v, "transform(v + 10 на месте)");

    // replace: заменить все '11' (бывшие '1') на '99'
    std::replace(v.begin(), v.end(), 11, 99);
    printContainer(v, "replace(11 -> 99)");

    // replace_if: заменить все числа > 15 на 0
    std::replace_if(v.begin(), v.end(), [](int x){ return x > 15; }, 0);
    printContainer(v, "replace_if(>15 -> 0)");

    // fill: заполнить dest значением 777
    std::fill(dest.begin(), dest.end(), 777);
    printContainer(dest, "fill(dest, 777)");

    // generate: заполнить dest числами 1, 2, 3...
    int n = 0;
    std::generate(dest.begin(), dest.end(), [&n](){ return ++n; });
    printContainer(dest, "generate(1, 2, 3...)");

    // remove: "удалить" все 0 из v (возвращает новый логический конец)
    v = original_v; // Сброс v
    v.push_back(0); v.push_back(3); v.push_back(0); // Добавим нулей для примера
    printContainer(v, "v перед remove(0)");
    auto new_end_remove = std::remove(v.begin(), v.end(), 3);
    printContainer(v, "v ПОСЛЕ remove(3), ДО erase"); // Покажет мусор в конце
    v.erase(new_end_remove, v.end()); // Фактическое удаление
    printContainer(v, "v ПОСЛЕ remove(3) и erase");

    // remove_if: удалить четные
    auto new_end_remove_if = std::remove_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    v.erase(new_end_remove_if, v.end());
    printContainer(v, "v после remove_if(четные) + erase");

    // unique: удалить идущие подряд дубликаты (нужна сортировка!)
    v = original_v; // Сброс v
    std::sort(v.begin(), v.end());
    printContainer(v, "v отсортированный перед unique");
    auto new_end_unique = std::unique(v.begin(), v.end());
    v.erase(new_end_unique, v.end());
    printContainer(v, "v после unique + erase");

    // reverse: перевернуть строку s
    std::reverse(s.begin(), s.end());
    printContainer(s, "reverse(s)");
    std::reverse(s.begin(), s.end()); // Вернем обратно

    // rotate: циклический сдвиг v (первые 3 элемента в конец)
    v = original_v; // Сброс v
    std::rotate(v.begin(), v.begin() + 3, v.end());
    printContainer(v, "rotate(v, +3)");


    // === 3. СОРТИРОВКА И УПОРЯДОЧИВАНИЕ ===
    std::cout << "=== 3. СОРТИРОВКА И УПОРЯДОЧИВАНИЕ ===" << std::endl;
    v = original_v; // Сброс v

    // sort: сортировка по возрастанию
    std::sort(v.begin(), v.end());
    printContainer(v, "sort(v)");

    // is_sorted: проверка сортировки
    std::cout << "is_sorted(v): " << std::is_sorted(v.begin(), v.end()) << std::endl;

    // sort: сортировка по убыванию (с лямбда-компаратором)
    std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });
    printContainer(v, "sort(v, убывание)");
    std::cout << "is_sorted(v, убывание): " << std::is_sorted(v.begin(), v.end(), std::greater<int>()) << std::endl;

    // stable_sort: стабильная сортировка (сохраняет порядок равных) - на int не видно, но важно для объектов
    // Пример: если были пары {(1, 'a'), (5, 'b'), (1, 'c')} -> sort может дать {(1,'a'), (1,'c'), (5,'b')} или {(1,'c'), (1,'a'), (5,'b')}
    // stable_sort ГАРАНТИРУЕТ {(1, 'a'), (1, 'c'), (5, 'b')} (порядок 'a' и 'c' сохранен)
    v = original_v; // Сброс v
    std::stable_sort(v.begin(), v.end());
    printContainer(v, "stable_sort(v)"); // Результат как у sort для int

    // partial_sort: первые 3 наименьших элемента будут отсортированы в начале
    v = original_v; // Сброс v
    std::partial_sort(v.begin(), v.begin() + 3, v.end());
    printContainer(v, "partial_sort(v, top 3)"); // Первые 3 - наименьшие и отсортированы

    // nth_element: поместить k-й элемент (медиану) на его место
    v = original_v; // Сброс v
    auto median_it = v.begin() + v.size() / 2;
    std::nth_element(v.begin(), median_it, v.end());
    printContainer(v, "nth_element(v, медиана)"); // Элемент на позиции median_it - истинная медиана
    std::cout << "Медиана (v[" << v.size()/2 << "]): " << *median_it << std::endl;

    // partition: разделить на четные и нечетные (порядок не гарантирован)
    v = original_v; // Сброс v
    auto part_it = std::partition(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    printContainer(v, "partition(v, четные/нечетные)");
    printRange(v.begin(), part_it, "  Четные");
    printRange(part_it, v.end(), "  Нечетные");
    std::cout << "\n";


    // === 4. БИНАРНЫЙ ПОИСК (на отсортированных данных) ===
    std::cout << "=== 4. БИНАРНЫЙ ПОИСК ===" << std::endl;
    std::vector<int> v_sorted = {1, 2, 4, 4, 5, 7, 9};
    printContainer(v_sorted, "v_sorted для бин. поиска");

    // binary_search: проверить наличие '4' и '6'
    bool has_4 = std::binary_search(v_sorted.begin(), v_sorted.end(), 4);
    bool has_6 = std::binary_search(v_sorted.begin(), v_sorted.end(), 6);
    std::cout << "binary_search(4): " << has_4 << ", binary_search(6): " << has_6 << std::endl;

    // lower_bound: найти первый элемент >= 4
    auto lb = std::lower_bound(v_sorted.begin(), v_sorted.end(), 4);
    std::cout << "lower_bound(4): значение " << *lb << " на позиции " << std::distance(v_sorted.begin(), lb) << std::endl;

    // upper_bound: найти первый элемент > 4
    auto ub = std::upper_bound(v_sorted.begin(), v_sorted.end(), 4);
    std::cout << "upper_bound(4): значение " << *ub << " на позиции " << std::distance(v_sorted.begin(), ub) << std::endl;

    // equal_range: найти диапазон элементов == 4
    auto range = std::equal_range(v_sorted.begin(), v_sorted.end(), 4);
    std::cout << "equal_range(4): диапазон от индекса " << std::distance(v_sorted.begin(), range.first)
              << " до " << std::distance(v_sorted.begin(), range.second) << std::endl;
    printRange(range.first, range.second, "  Элементы == 4");
    std::cout << "\n";


    // === 5. СЛИЯНИЕ (на отсортированных данных) ===
    std::cout << "=== 5. СЛИЯНИЕ ===" << std::endl;
    std::vector<int> part1 = {1, 3, 5, 7};
    std::vector<int> part2 = {2, 4, 6, 8};
    std::vector<int> merged_dest(part1.size() + part2.size());
    printContainer(part1, "part1");
    printContainer(part2, "part2");

    // merge: слить part1 и part2 в merged_dest
    std::merge(part1.begin(), part1.end(), part2.begin(), part2.end(), merged_dest.begin());
    printContainer(merged_dest, "merge(part1, part2)");
    std::cout << "\n";


    // === 6. КУЧИ (Heap) ===
    std::cout << "=== 6. КУЧИ (Heap) ===" << std::endl;
    v = original_v; // Сброс v
    printContainer(v, "v перед make_heap");

    // make_heap: сделать из v max-кучу
    std::make_heap(v.begin(), v.end());
    printContainer(v, "make_heap(v)"); // v[0] - максимальный элемент

    // push_heap: добавить элемент 10 в кучу
    v.push_back(10);
    printContainer(v, "v перед push_heap(10)");
    std::push_heap(v.begin(), v.end());
    printContainer(v, "v после push_heap(10)");

    // pop_heap: переместить максимальный элемент в конец
    std::pop_heap(v.begin(), v.end()); // Максимум теперь в v.back()
    int max_val = v.back();
    v.pop_back(); // Удаляем его
    std::cout << "pop_heap: извлечен максимум " << max_val << std::endl;
    printContainer(v, "v после pop_heap");

    // sort_heap: отсортировать кучу
    std::sort_heap(v.begin(), v.end());
    printContainer(v, "sort_heap(v)");
    std::cout << "\n";


    // === 7. МИНИМУМ / МАКСИМУМ ===
    std::cout << "=== 7. МИНИМУМ / МАКСИМУМ ===" << std::endl;
    v = original_v; // Сброс v
    printContainer(v, "v для min/max");

    // min, max
    std::cout << "min(3, 7): " << std::min(3, 7) << ", max(3, 7): " << std::max(3, 7) << std::endl;

    // minmax
    auto pair_minmax = std::minmax({5, 2, 8, 1, 9}); // Можно на initializer_list
    std::cout << "minmax({5, 2, 8, 1, 9}): min=" << pair_minmax.first << ", max=" << pair_minmax.second << std::endl;

    // min_element, max_element
    auto it_min = std::min_element(v.begin(), v.end());
    auto it_max = std::max_element(v.begin(), v.end());
    std::cout << "min_element(v): " << *it_min << ", max_element(v): " << *it_max << std::endl;

    // minmax_element
    auto pair_it_minmax = std::minmax_element(v.begin(), v.end());
    std::cout << "minmax_element(v): min=" << *pair_it_minmax.first << " на поз. " << std::distance(v.begin(), pair_it_minmax.first)
              << ", max=" << *pair_it_minmax.second << " на поз. " << std::distance(v.begin(), pair_it_minmax.second) << std::endl;
    std::cout << "\n";


    // === 8. ЧИСЛОВЫЕ АЛГОРИТМЫ (<numeric>) ===
    std::cout << "=== 8. ЧИСЛОВЫЕ АЛГОРИТМЫ (<numeric>) ===" << std::endl;
    v = {1, 2, 3, 4, 5};
    printContainer(v, "v для numeric");

    // inner_product: скалярное произведение v и v
    long long dot_product = std::inner_product(v.begin(), v.end(), v.begin(), 0LL);
    std::cout << "inner_product(v, v, 0): " << dot_product << std::endl;

    // partial_sum: частичные суммы v в dest_numeric
    std::vector<int> dest_numeric(v.size());
    std::partial_sum(v.begin(), v.end(), dest_numeric.begin());
    printContainer(dest_numeric, "partial_sum(v)"); // [1, 3, 6, 10, 15]

    // iota: заполнить вектор числами начиная с 100
    std::vector<int> iota_vec(5);
    std::iota(iota_vec.begin(), iota_vec.end(), 100);
    printContainer(iota_vec, "iota(vec, 100)"); // [100, 101, 102, 103, 104]
    std::cout << "\n";


    std::cout << "--- КОНЕЦ ДЕМОНСТРАЦИИ ---" << std::endl;

    return 0;
}
