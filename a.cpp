#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Point {
public:
    int x;
    int y;

    Point(int d, int m) : x(d), y(m) {}
    Point(int d) : x(d), y(0) {}
    Point() : x(0), y(0) {}

    Point operator-(const Point& s) const {
        return Point(x - s.x, y - s.y);
    }

    Point operator+(const Point& s) const {
        return Point(x + s.x, y + s.y);
    }

    Point operator*(double scalar) const {
        return Point(static_cast<int>(x * scalar), static_cast<int>(y * scalar));
    }

    void View() const {
        cout << x << ' ' << y << endl;
    }

    double Dist() const {
        return sqrt(x * x + y * y);
    }
};

class Line {
public:
    int A; 
    int B;
    int C; 

    Line(int a, int b, int c) : A(a), B(b), C(c) {}
    Line(Point p1, Point p2) {
        A = p2.y - p1.y; 
        B = p1.x - p2.x;
        C = -A * p1.x - B * p1.y; 
    }

    void View() const {
        cout << A << "*x + " << B << "*y + " << C << " = 0" << endl;
    }

    bool dotPos(const Point& u) const {
        return A * u.x + B * u.y + C > 0;
    }

    double Dist(const Point& a) const {
        return abs(A * a.x + B * a.y + C) / sqrt(A * A + B * B);
    }
};

class Segment {
public:
    Point first; 
    Point second; 

    Segment(Point a, Point b) : first(a), second(b) {}

    double Dist(const Point& a) {
        Point v = second - first; // Вектор, направленный вдоль отрезка (от first к second)
        Point w = a - first;     // Вектор от начала отрезка (first) до заданной точки 'a'

        double c1 = w.x * v.x + w.y * v.y; // Скалярное произведение векторов w и v. Проекция w на v.
        if (c1 <= 0) {
            return (a - first).Dist(); // Если проекция "за пределами" начала отрезка, то ближайшая точка - начало отрезка (first)
        }

        double c2 = v.x * v.x + v.y * v.y; // Скалярное произведение v на себя. Квадрат длины вектора v.
        if (c2 <= c1) {
            return (a - second).Dist(); // Если проекция "за пределами" конца отрезка, то ближайшая точка - конец отрезка (second)
        }

        double b = c1 / c2; // Параметр проекции точки 'a' на прямую, содержащую отрезок. Значение от 0 до 1 соответствует проекции на сам отрезок.
        Point Pb = first + v * b; // Точка проекции 'Pb' точки 'a' на прямую, содержащую отрезок.
        return (a - Pb).Dist();     // Расстояние от точки 'a' до ее проекции 'Pb' - это и есть расстояние до отрезка.
    }
};

class Quadro {
public:
    Point points[4];

    Quadro(Point p1, Point p2, Point p3, Point p4) {
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;
    }

    void View() const {
        cout << "Square points:" << endl;
        for (int i = 0; i < 4; ++i) {
            cout << "P" << i + 1 << ": ";
            points[i].View();
        }
    }

    // Метод для вычисления расстояния от точки до четырехугольника. Находит минимальное расстояние до каждой из сторон четырехугольника.
    double Dist(const Point& p) const {
        Segment sides[4] = { // Создаем массив отрезков, представляющих стороны четырехугольника
            Segment(points[0], points[1]),
            Segment(points[1], points[2]),
            Segment(points[2], points[3]),
            Segment(points[3], points[0])
        };

        double minDist = sides[0].Dist(p); // Инициализируем минимальное расстояние расстоянием до первой стороны
        for (int i = 1; i < 4; i++) {
            minDist = min(minDist, sides[i].Dist(p)); // Находим минимум расстояния среди всех сторон
        }
        return minDist; // Возвращаем минимальное расстояние - расстояние от точки до четырехугольника.
    }

    bool is_inside(const Point& p) const {
        Line lines[4] = {
            Line(points[0], points[1]),
            Line(points[1], points[2]),
            Line(points[2], points[3]),
            Line(points[3], points[0])
        };

        for (int i = 0; i < 4; ++i) {
            if (lines[i].dotPos(p)) { // Проверяем положение точки относительно каждой прямой. Если точка с "положительной" стороны хотя бы одной прямой, то она снаружи.
                return false; // Точка снаружи четырехугольника.
            }
        }
        return true; // Точка не находится с "положительной" стороны ни одной из прямых, значит, она внутри или на границе четырехугольника.
    }
};


int main() {
    Point s(1, 1);
    Point d(0, 0); 

    Line(s, d).View(); 
    Line(d, s).View();

    cout << endl;
    cout << "Point (-1, 1) is on the positive side of Line(d, s): " << Line(d, s).dotPos(Point(-1, 1)) << endl; // Проверяем положение точки (-1, 1) относительно прямой (d, s).
    cout << "Point (1, -1) is on the positive side of Line(d, s): " << Line(d, s).dotPos(Point(1, -1)) << endl; // Проверяем положение точки (1, -1) относительно прямой (d, s).

    cout << endl;
    Segment seg(Point(0, 0), Point(2, 2)); // Создаем отрезок 'seg' с концами в (0, 0) и (2, 2).
    cout << "Distance from Point(3, 0) to segment: " << seg.Dist(Point(3, 0)) << endl;   // Вычисляем расстояние от точки (3, 0) до отрезка 'seg'.
    cout << "Distance from Point(1, 1) to segment: " << seg.Dist(Point(1, 1)) << endl;   // Вычисляем расстояние от точки (1, 1) до отрезка 'seg'. (Точка лежит на отрезке, расстояние 0)
    cout << "Distance from Point(2, 0) to segment: " << seg.Dist(Point(2, 0)) << endl;   // Вычисляем расстояние от точки (2, 0) до отрезка 'seg'.

    cout << endl;
    Point sq_p1(0, 0);
    Point sq_p2(2, 0);
    Point sq_p3(2, 2);
    Point sq_p4(0, 2);

    Quadro square(sq_p1, sq_p2, sq_p3, sq_p4);
    square.View();

    cout << endl;
    Point p_outside(3, 1);
    Point p_inside(1, 1);
    Point p_on_line(1, 0);
    Point p_boundary_vertex(0, 0);

    cout << endl;
    cout << "Distance from Point(3, 1) to square: " << square.Dist(p_outside) << endl;          // от внешней точки до квадрата.
    cout << "Distance from Point(1, 1) to square: " << square.Dist(p_inside) << endl;           // =0.
    cout << "Distance from Point(1, 0) to square: " << square.Dist(p_on_line) << endl;          // от точки на стороне до квадрата (должно быть 0).
    cout << "Distance from Point(0, 0) to square: " << square.Dist(p_boundary_vertex) << endl;  // от точки в вершине до квадрата (должно быть 0).

    cout << endl;
    cout << "Is Point(3, 1) inside square? " << square.is_inside(p_outside) << endl;           // внешняя точка внутри квадрата?
    cout << "Is Point(1, 1) inside square? " << square.is_inside(p_inside) << endl;            // внутренняя точка внутри квадрата?
    cout << "Is Point(1, 0) inside square? " << square.is_inside(p_on_line) << endl;           // на стороне внутри квадрата?
    cout << "Is Point(0, 0) inside square? " << square.is_inside(p_boundary_vertex) << endl;   // в вершине внутри квадрата?

    return 0; 
}