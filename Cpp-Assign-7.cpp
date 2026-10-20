#include <iostream>
using namespace std;
 
// ---------- 1. Function overloading ----------
// Same function name, different parameter lists. The compiler selects the
// version at compile time by matching the arguments (early binding).
class MathOps {
public:
    int add(int a, int b) {
        cout << "  add(int, int) called" << endl;
        return a + b;
    }
    double add(double a, double b) {
        cout << "  add(double, double) called" << endl;
        return a + b;
    }
    int add(int a, int b, int c) {
        cout << "  add(int, int, int) called" << endl;
        return a + b + c;
    }
};
 
// ---------- 2. Operator overloading ----------
class Complex {
private:
    double real, imag;
 
public:
    Complex() : real(0), imag(0) {}                       // default constructor
    Complex(double r, double i) : real(r), imag(i) {}     // parameterized constructor
 
    Complex operator+(const Complex &o) const {           // c1 + c2
        return Complex(real + o.real, imag + o.imag);
    }
    Complex operator*(const Complex &o) const {           // c1 * c2
        return Complex(real * o.real - imag * o.imag,
                       real * o.imag + imag * o.real);
    }
    bool operator==(const Complex &o) const {             // c1 == c2
        return real == o.real && imag == o.imag;
    }
    friend ostream &operator<<(ostream &os, const Complex &c);
};
 
ostream &operator<<(ostream &os, const Complex &c) {
    os << c.real << (c.imag < 0 ? " - " : " + ") << (c.imag < 0 ? -c.imag : c.imag) << "i";
    return os;
}
 
int main() {
    MathOps m;
    int a, b, x, y, z;
    double p, q;
    double r1, i1, r2, i2;
 
    cout << "Enter two integers: ";
    cin >> a >> b;
    cout << "Enter two decimal numbers: ";
    cin >> p >> q;
    cout << "Enter three integers: ";
    cin >> x >> y >> z;
    cout << "Enter real and imaginary part of complex number 1: ";
    cin >> r1 >> i1;
    cout << "Enter real and imaginary part of complex number 2: ";
    cin >> r2 >> i2;
 
    cout << "\n=== Function Overloading ===" << endl;
    int sum1 = m.add(a, b);                               // add(int, int)
    cout << "  " << a << " + " << b << " = " << sum1 << endl;
    double sum2 = m.add(p, q);                            // add(double, double)
    cout << "  " << p << " + " << q << " = " << sum2 << endl;
    int sum3 = m.add(x, y, z);                            // add(int, int, int)
    cout << "  " << x << " + " << y << " + " << z << " = " << sum3 << endl;
 
    cout << "\n=== Operator Overloading ===" << endl;
    Complex c1(r1, i1), c2(r2, i2), c3;                   // c3 uses the default constructor
    cout << "  c1 = " << c1 << endl;
    cout << "  c2 = " << c2 << endl;
    c3 = c1 + c2;
    cout << "  c1 + c2 = " << c3 << endl;
    c3 = c1 * c2;
    cout << "  c1 * c2 = " << c3 << endl;
    cout << "  c1 == c2 ? " << (c1 == c2 ? "Yes" : "No") << endl;
 
    return 0;
}
 



#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
 
const double PI = 3.14159;
 
// ---------- 1. Early binding vs late binding ----------
class Animal {
public:
    void sound() const { cout << "  Animal::sound()  - non-virtual, Animal version" << endl; }
    virtual void speak() const { cout << "  Animal::speak()  - virtual, Animal version" << endl; }
    virtual ~Animal() {}
};
 
class Dog : public Animal {
public:
    void sound() const { cout << "  Dog::sound()     - hides the base function" << endl; }
    void speak() const override { cout << "  Dog::speak()     - overrides the base function" << endl; }
};
 
// ---------- 2. Abstract class and virtual functions ----------
class Shape {                                   // abstract class: has a pure virtual function
protected:
    string name;
 
public:
    Shape(string n) : name(n) {}
    virtual double area() const = 0;            // pure virtual function
    virtual void display() const {              // virtual function with a body
        cout << "  " << name << " area = " << area() << endl;
    }
    virtual ~Shape() { cout << "  Shape destructor called" << endl; }   // virtual destructor
};
 
class Circle : public Shape {
private:
    double radius;
 
public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    double area() const override { return PI * radius * radius; }
    ~Circle() { cout << "  Circle destructor called" << endl; }
};
 
class Rectangle : public Shape {
private:
    double length, breadth;
 
public:
    Rectangle(double l, double b) : Shape("Rectangle"), length(l), breadth(b) {}
    double area() const override { return length * breadth; }
    ~Rectangle() { cout << "  Rectangle destructor called" << endl; }
};
 
class Triangle : public Shape {
private:
    double base, height;
 
public:
    Triangle(double b, double h) : Shape("Triangle"), base(b), height(h) {}
    double area() const override { return 0.5 * base * height; }
    ~Triangle() { cout << "  Triangle destructor called" << endl; }
};
 
int main() {
    double radius, length, breadth, base, height;
 
    cout << "Enter radius of circle: ";
    cin >> radius;
    cout << "Enter length and breadth of rectangle: ";
    cin >> length >> breadth;
    cout << "Enter base and height of triangle: ";
    cin >> base >> height;
 
    cout << fixed << setprecision(2);
 
    cout << "\n=== Early binding vs Late binding (base pointer to derived object) ===" << endl;
    Animal *a = new Dog();
    a->sound();                                 // decided at compile time -> Animal version
    a->speak();                                 // decided at run time     -> Dog version
    delete a;
 
    cout << "\n=== Run-time polymorphism using base class pointers ===" << endl;
    Shape *shapes[3];
    shapes[0] = new Circle(radius);
    shapes[1] = new Rectangle(length, breadth);
    shapes[2] = new Triangle(base, height);
 
    double total = 0;
    for (int i = 0; i < 3; i++) {
        shapes[i]->display();                   // the version called depends on the real object
        total += shapes[i]->area();
    }
    cout << "  Total area = " << total << endl;
 
    cout << "\n=== Virtual destructor: objects deleted through base pointers ===" << endl;
    for (int i = 0; i < 3; i++)
        delete shapes[i];                       // derived destructor runs first, then base
 
    return 0;
}
 