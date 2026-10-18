#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    float marks;
    static int count;                 // static data member: one copy shared by all objects

public:
    // 'this' resolves the clash between parameter names and data member names
    Student(int rollNo, string name, float marks) {
        this->rollNo = rollNo;
        this->name = name;
        this->marks = marks;
        count++;
    }

    // returning *this allows function chaining: s.setName("A").setMarks(50)
    Student &setName(string name) {
        this->name = name;
        return *this;
    }
    Student &setMarks(float marks) {
        this->marks = marks;
        return *this;
    }

    // inline functions: short bodies, expanded at the call point
    inline bool isPass() const { return marks >= 40; }
    inline float getMarks() const { return marks; }

    // 'this' holds the address of the calling object
    void showAddress() const {
        cout << name << ": address of object = " << this << endl;
    }

    // compares the calling object with another and returns the topper
    const Student &topper(const Student &other) const {
        if (marks >= other.marks)
            return *this;
        return other;
    }

    void display() const {
        cout << "Roll No: " << rollNo << ", Name: " << name
             << ", Marks: " << marks
             << ", Result: " << (isPass() ? "Pass" : "Fail") << endl;
    }

    // static member function: no 'this', can use only static members
    static int getCount() { return count; }

    ~Student() { count--; }
};

int Student::count = 0;               // definition of the static data member

int main() {
    cout << "Students before creating objects: " << Student::getCount() << endl;

    int r1, r2;
    string n1, n2;
    float m1, m2;

    cout << "Enter roll no, name and marks of student 1: ";
    cin >> r1 >> n1 >> m1;
    cout << "Enter roll no, name and marks of student 2: ";
    cin >> r2 >> n2 >> m2;

    Student s1(r1, n1, m1);
    Student s2(r2, n2, m2);

    cout << "\n--- Objects and member functions ---" << endl;
    s1.display();
    s2.display();

    cout << "\n--- this pointer ---" << endl;
    s1.showAddress();
    s2.showAddress();
    cout << "Address of s1 (&s1)     = " << &s1 << endl;

    cout << "\n--- Function chaining using this ---" << endl;
    s2.setName("Updated").setMarks(m2 + 5);
    s2.display();

    cout << "\n--- Inline functions ---" << endl;
    cout << "s1 marks = " << s1.getMarks() << ", pass = " << s1.isPass() << endl;

    cout << "\n--- Static member function ---" << endl;
    cout << "Students created so far: " << Student::getCount() << endl;

    cout << "\n--- Topper (returned using *this) ---" << endl;
    s1.topper(s2).display();

    return 0;
}

#include <iostream>
using namespace std;

class Rectangle;                      // forward declaration

// Calculator is a friend of Rectangle: it can access Rectangle's private members
class Calculator {
public:
    double area(const Rectangle &r);
    double perimeter(const Rectangle &r);
    void scale(Rectangle &r, double factor);   // modifies private data
    void show(const Rectangle &r);
};

class Rectangle {
private:
    double length;
    double breadth;

public:
    Rectangle(double l, double b) : length(l), breadth(b) {}

    friend class Calculator;          // grants Calculator access to private members
};

double Calculator::area(const Rectangle &r) {
    return r.length * r.breadth;      // direct access to private data
}

double Calculator::perimeter(const Rectangle &r) {
    return 2 * (r.length + r.breadth);
}

void Calculator::scale(Rectangle &r, double factor) {
    r.length *= factor;
    r.breadth *= factor;
}

void Calculator::show(const Rectangle &r) {
    cout << "Length = " << r.length << ", Breadth = " << r.breadth << endl;
}

int main() {
    double l, b, f;
    cout << "Enter length and breadth: ";
    cin >> l >> b;
    cout << "Enter scale factor: ";
    cin >> f;

    Rectangle rect(l, b);
    Calculator calc;                  // friendship is one-way: Rectangle cannot
                                      // access private members of Calculator
    cout << "\n--- Original rectangle ---" << endl;
    calc.show(rect);
    cout << "Area      = " << calc.area(rect) << endl;
    cout << "Perimeter = " << calc.perimeter(rect) << endl;

    calc.scale(rect, f);

    cout << "\n--- After scaling by " << f << " ---" << endl;
    calc.show(rect);
    cout << "Area      = " << calc.area(rect) << endl;
    cout << "Perimeter = " << calc.perimeter(rect) << endl;

    return 0;
}