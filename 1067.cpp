#include <iostream>
#include <vector>  
#include <string> 
#include <map>      // Для использования std::map (сортированное хранение детей)
#include <sstream>  // Для удобного разделения строки пути (std::stringstream)
#include <memory>   // Для умных указателей (std::unique_ptr)

using namespace std;

struct DirectoryNode {
    // Нам не нужно хранить имя в самом узле, так как оно будет ключом в map родителя.
    // Главное - хранить дочерние узлы.
    // Используем map, чтобы дети автоматически хранились в лексикографическом порядке имен.
    // Ключ - имя подкаталога (string).
    // Значение - умный указатель на узел подкаталога (unique_ptr<DirectoryNode>).
    // unique_ptr автоматически управляет памятью узлов.
    map<string, unique_ptr<DirectoryNode>> children;
};

// Рекурсивная функция для печати дерева каталогов
// name - имя текущего каталога для печати
// node - узел текущего каталога
// depth - текущий уровень вложенности (для отступов)
void printTree(const string& name, const DirectoryNode& node, int depth) {
    // Печатаем отступ: 'depth' пробелов
    for (int i = 0; i < depth; ++i) {
        cout << " ";
    }
    // Печатаем имя текущего каталога
    cout << name << "\n";

    // Рекурсивно вызываем печать для всех дочерних каталогов.
    // Так как используем map, итерация по children будет происходить
    // в лексикографическом порядке ключей (имен подкаталогов).
    for (const auto& pair : node.children) {
        const string& child_name = pair.first;       // Имя дочернего каталога
        const auto& child_node_ptr = pair.second;    // Указатель на узел дочернего каталога
        printTree(child_name, *child_node_ptr, depth + 1); // Вызов для ребенка с увеличенной глубиной
    }
}

// Функция для разделения строки пути на компоненты (имена каталогов)
vector<string> splitPath(const string& path) {
    vector<string> parts;
    stringstream ss(path); // Создаем строковый поток из пути
    string segment;
    // Используем getline с разделителем '\' для извлечения имен каталогов
    while (getline(ss, segment, '\\')) {
        // Проверяем, что сегмент не пустой (на случай двойных слешей или слеша в конце/начале)
        if (!segment.empty()) {
            parts.push_back(segment);
        }
    }
    return parts;
}

int main() {
    int n; // Количество путей
    cin >> n;

    // Используем map для хранения корневых каталогов.
    // Это как бы "дети" невидимого корневого узла всей файловой системы.
    // Они будут автоматически отсортированы по имени.
    map<string, unique_ptr<DirectoryNode>> root_directories;

    // Считываем и обрабатываем каждый путь
    for (int i = 0; i < n; ++i) {
        string path_str;
        cin >> path_str;

        // Разделяем путь на компоненты
        vector<string> parts = splitPath(path_str);

        // Начинаем вставку с уровня корневых каталогов
        map<string, unique_ptr<DirectoryNode>>* current_level_map = &root_directories;

        // Проходим по каждому компоненту пути
        for (const string& part : parts) {
            // Ищем каталог с именем 'part' на текущем уровне
            auto it = current_level_map->find(part);

            // Если каталог не найден...
            if (it == current_level_map->end()) {
                // ...создаем новый узел для этого каталога...
                auto new_node = make_unique<DirectoryNode>();
                // ...и вставляем его в map текущего уровня.
                // insert возвращает пару, где .first - итератор на вставленный элемент.
                it = current_level_map->insert({part, std::move(new_node)}).first;
            }

            // Переходим на уровень ниже: теперь текущий уровень - это map дочерних
            // каталогов только что найденного или созданного узла 'part'.
            current_level_map = &(it->second->children);
        }
    }

    // Печатаем все дерево, начиная с корневых каталогов
    // Итерация по root_directories происходит в отсортированном порядке имен.
    for (const auto& pair : root_directories) {
        const string& root_name = pair.first;
        const auto& root_node_ptr = pair.second;
        // Вызываем рекурсивную печать для каждого корневого каталога (глубина 0)
        printTree(root_name, *root_node_ptr, 0);
    }

    return 0;
}
