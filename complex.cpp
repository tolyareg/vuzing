#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double fake;

    Complex(double r = 0.0, double i = 0.0) : real(r), fake(i) {}

    Complex operator+(const Complex& other) {
        return Complex(real + other.real, fake + other.fake);
    }

    Complex operator-(const Complex& other) {
        return Complex(real - other.real, fake - other.fake);
    }

    Complex operator*(const Complex& other) {
        double newReal = (real * other.real) - (fake * other.fake);
        double newFake = (real * other.fake) + (fake * other.real);
        return Complex(newReal, newFake);
    }

    Complex operator/(const Complex& other) {
        double del = (other.real * other.real) + (other.fake * other.fake);
        double newReal = ((real * other.real) + (fake * other.fake)) / del;
        double newFake = ((fake * other.real) - (real * other.fake)) / del;

        return Complex(newReal, newFake);
    }

    void View() {
        cout << real;
        if (fake >= 0) {
            cout << "+" << fake << "i";
        } else {
            cout << fake << "i";
        }
    }
};

int main() {
    Complex z1(3.0, 2.0);
    Complex z2(1.0, -1.0);

    cout << "z1 = "; z1.View(); cout << endl;
    cout << "z2 = "; z2.View(); cout << endl;

    Complex sum = z1 + z2;
    cout << "z1 + z2 = "; sum.View(); cout << endl;

    Complex raznost = z1 - z2;
    cout << "z1 - z2 = "; raznost.View(); cout << endl;

    Complex proizv = z1 * z2;
    cout << "z1 * z2 = "; proizv.View(); cout << endl;

    Complex chastnoe = z1 / z2;
    cout << "z1 / z2 = "; chastnoe.View(); cout << endl;

    return 0;
}
