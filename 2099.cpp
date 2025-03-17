#include <iostream>

using namespace std;

class Point3D {
public:
    long long x, y, z;

    Point3D(long long x_ = 0, long long y_ = 0, long long z_ = 0) : x(x_), y(y_), z(z_) {}

    long long dot_product(const Point3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Point3D cross_product(const Point3D& other) const {
        return Point3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Distance to another point (without using <cmath>)
    double distance(const Point3D& other) const {
        long long dx = x - other.x;
        long long dy = y - other.y;
        long long dz = z - other.z;
        long long sq_dist = dx * dx + dy * dy + dz * dz;

        if (sq_dist == 0) return 0.0;

        double guess = (double)sq_dist;
        double prev_guess;

        do {
            prev_guess = guess;
            guess = (guess + sq_dist / guess) / 2.0;
        } while (my_abs(guess - prev_guess) > 1e-9); 

        return guess;
    }


    Point3D operator-(const Point3D& other) const {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }

    Point3D operator+(const Point3D& other) const {
        return Point3D(x + other.x, y + other.y, z + other.z);
    }

    bool operator==(const Point3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

private:
    double my_abs(double val) const {
        return (val < 0) ? -val : val;
    }
};



class Line3D {
public:
    Point3D point; 
    Point3D direction;

    Line3D(const Point3D& p1, const Point3D& p2) : point(p1), direction(p2 - p1) {}


    double distance_to_point(const Point3D& p) const {
          if (direction.x == 0 && direction.y == 0 && direction.z == 0)
          {
            return point.distance(p);
          }
        Point3D vec = p - point;
        return (vec.cross_product(direction)).distance(Point3D(0,0,0)) / direction.distance(Point3D(0,0,0));
    }
};


class Plane3D {
public:
    long long a, b, c, d;

    Plane3D(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
        Point3D v1 = p2 - p1;
        Point3D v2 = p3 - p1;
        Point3D normal = v1.cross_product(v2);
        a = normal.x;
        b = normal.y;
        c = normal.z;
        d = -(a * p1.x + b * p1.y + c * p1.z);
    }
    
    Plane3D(const Point3D& normal, const Point3D& p1)
    {
      a = normal.x;
      b = normal.y;
      c = normal.z;
      d = -(a*p1.x + b*p1.y + c*p1.z);
    }

    Plane3D(long long a_, long long b_, long long c_, long long d_) : a(a_), b(b_), c(c_), d(d_){}

    Point3D normal_vector() const {
        return Point3D(a, b, c);
    }


  double distance_to_point(const Point3D& p) const {
      
    double numerator = my_abs((double)(a * p.x + b * p.y + c * p.z + d));
    
    long long sq_sum = a*a + b*b + c*c;
    if(sq_sum == 0) return 0;
    
    double guess = (double)sq_sum;
    double prev_guess = 0.0;
    
    do {
        prev_guess = guess;
        guess = (guess + sq_sum / guess) / 2.0;
    }while(my_abs(guess - prev_guess) > 1e-9);

    double denominator = guess;
    
    return numerator / denominator;
  }
    //   > 0:  right
    //   < 0:  left
    //   = 0:  on line
    long long side_of_plane(const Point3D& p) const {
        return a * p.x + b * p.y + c * p.z + d;
    }

private:
     double my_abs(double val) const {
        return (val < 0) ? -val : val;
    }
};


int main() {
    Point3D p1(1, 2, 3);
    Point3D p2(4, 5, 6);
    cout << "p1 distance to p2: " << p1.distance(p2) << endl;
    cout << "p1 dot product p2: " << p1.dot_product(p2) << endl;
    Point3D p3 = p1.cross_product(p2);
    cout << "p1 cross product p2: (" << p3.x << ", " << p3.y << ", " << p3.z << ")" << endl;

    Line3D line(p1, p2);
    Point3D p4(7, 8, 9);
    cout << "Distance from p4 to line(p1, p2): " << line.distance_to_point(p4) << endl;

    Plane3D plane1(p1, p2, p4);
    cout << "Plane equation: " << plane1.a << "x + " << plane1.b << "y + " << plane1.c << "z + " << plane1.d << " = 0" << endl;
    Point3D normal = plane1.normal_vector();
    cout << "Normal vector: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << endl;
    cout << "Distance from origin to plane: " << plane1.distance_to_point(Point3D(0, 0, 0)) << endl;

    Point3D p5(0,0,0);
    long long side = plane1.side_of_plane(p5);
    cout << "Point p5 is on side: " << side << " (";
     if (side > 0) {
        cout << "positive/right" << endl;
    } else if (side < 0) {
        cout << "negative/left" << endl;
    } else {
        cout << "on the plane" << endl;
    }
    
    Plane3D plane2(1,1,1,-3); //x+y+z-3= 0;
    Point3D check(1,1,1);
    cout << plane2.side_of_plane(check) << endl; 

    return 0;
}
