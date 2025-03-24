#include <iostream>
using namespace std;


struct E {
    int weight;// ves
    int first, second;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    int counter = 0; // kol-vo рёбер??.
    
    int ** weigth = new int * [n+1];
    int * color = new int [n+1];
    int * rank = new int [n+1] { 1 };
    
    int ne = 0;
    E* edge = new E[];
    
    for (int i = 1; i <= n; ++i) {
        color[i] = i;
        // rank[i] = i; // ne nuzhno
    }
    
    int ca, cb; // gorod gde nahoditsa electrostanciya
    cin >> ca;
    
    for (int i = 1; i <= m; ++i) {
        cin >> cb;
        // Union(ca, cb);
        color[cb] = color[ca];
        rank[cb]++;
        rank[ca]++;
        counter++;
    }
    
    int Answer = 0;
    
}

// union, find

// считать матрицу ??
// должен быть отсортирован массив рёбер, перед этим его нужно создать.
// если продем по верхней грани треугольна - мы найдем количество рёбер.
