#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
 
const double PI = 3.14159;
 
// ---------- Base class ----------
class Person {
protected:                            // visible in derived classes, hidden outside
    string name;
    int age;
 
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "  Person constructor called" << endl;
    }
    void displayPerson() const {
        cout << "  Name: " << name << ", Age: " << age << endl;
    }
    ~Person() { cout << "  Person destructor called" << endl; }
};
 
// ---------- 1. Single inheritance: Person -> Student ----------
class Student : public Person {
private:
    int rollNo;
    float marks;
 
public:
    Student(string n, int a, int r, float m) : Person(n, a), rollNo(r), marks(m) {
        cout << "  Student constructor called" << endl;
    }
    void display() const {
        displayPerson();              // inherited member function
        cout << "  Roll No: " << rollNo << ", Marks: " << marks << endl;
    }
    ~Student() { cout << "  Student destructor called" << endl; }
};
 
// ---------- 2. Multilevel inheritance: Person -> Employee -> Manager ----------
class Employee : public Person {
protected:
    int empId;
    double salary;
 
public:
    Employee(string n, int a, int id, double s) : Person(n, a), empId(id), salary(s) {
        cout << "  Employee constructor called" << endl;
    }
    void displayEmployee() const {
        displayPerson();
        cout << "  Employee ID: " << empId << ", Salary: " << salary << endl;
    }
    ~Employee() { cout << "  Employee destructor called" << endl; }
};
 
class Manager : public Employee {
private:
    int teamSize;
 
public:
    Manager(string n, int a, int id, double s, int t) : Employee(n, a, id, s), teamSize(t) {
        cout << "  Manager constructor called" << endl;
    }
    double bonus() const { return salary * 0.10; }   // uses protected 'salary' of Employee
    void display() const {
        displayEmployee();
        cout << "  Team Size: " << teamSize << ", Bonus (10%): " << bonus() << endl;
    }
    ~Manager() { cout << "  Manager destructor called" << endl; }
};
 
// ---------- 3. Hierarchical inheritance: Shape -> Circle, Rectangle ----------
class Shape {
protected:
    string type;
 
public:
    Shape(string t) : type(t) {}
    void showType() const { cout << "  Shape: " << type << endl; }
};
 
class Circle : public Shape {
private:
    double radius;
 
public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    double area() const { return PI * radius * radius; }
};
 
class Rectangle : public Shape {
private:
    double length, breadth;
 
public:
    Rectangle(double l, double b) : Shape("Rectangle"), length(l), breadth(b) {}
    double area() const { return length * breadth; }
};
 
int main() {
    string sName, mName;
    int sAge, roll, mAge, empId, team;
    float marks;
    double salary, radius, length, breadth;
 
    cout << "Enter student name, age, roll no, marks: ";
    cin >> sName >> sAge >> roll >> marks;
    cout << "Enter manager name, age, employee id, salary, team size: ";
    cin >> mName >> mAge >> empId >> salary >> team;
    cout << "Enter circle radius: ";
    cin >> radius;
    cout << "Enter rectangle length and breadth: ";
    cin >> length >> breadth;
 
    cout << fixed << setprecision(2);
 
    cout << "\n=== 1. Single Inheritance (Person -> Student) ===" << endl;
    {                                     // block: destructors run at the closing brace
        Student s(sName, sAge, roll, marks);
        s.display();
    }
 
    cout << "\n=== 2. Multilevel Inheritance (Person -> Employee -> Manager) ===" << endl;
    {
        Manager m(mName, mAge, empId, salary, team);
        m.display();
    }
 
    cout << "\n=== 3. Hierarchical Inheritance (Shape -> Circle, Rectangle) ===" << endl;
    Circle c(radius);
    Rectangle r(length, breadth);
    c.showType();
    cout << "  Area of circle    = " << c.area() << endl;
    r.showType();
    cout << "  Area of rectangle = " << r.area() << endl;
 
    return 0;
}
 


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
 
// ---------- 4. Multiple inheritance: Teacher + Researcher -> Professor ----------
class Teacher {
protected:
    string subject;
 
public:
    Teacher(string s) : subject(s) {
        cout << "  Teacher constructor called" << endl;
    }
    void info() const { cout << "  Teaches: " << subject << endl; }
    ~Teacher() { cout << "  Teacher destructor called" << endl; }
};
 
class Researcher {
protected:
    int papers;
 
public:
    Researcher(int p) : papers(p) {
        cout << "  Researcher constructor called" << endl;
    }
    void info() const { cout << "  Research papers published: " << papers << endl; }
    ~Researcher() { cout << "  Researcher destructor called" << endl; }
};
 
class Professor : public Teacher, public Researcher {
private:
    string name;
 
public:
    // base classes are constructed in the order of declaration in the class header
    Professor(string n, string s, int p) : Teacher(s), Researcher(p), name(n) {
        cout << "  Professor constructor called" << endl;
    }
    void display() const {
        cout << "  Professor: " << name << endl;
        // info() exists in both bases, so a plain info() call is ambiguous.
        // The scope resolution operator selects the required one.
        Teacher::info();
        Researcher::info();
    }
    ~Professor() { cout << "  Professor destructor called" << endl; }
};
 
// ---------- 5. Hybrid inheritance (diamond) using a virtual base class ----------
// Student is the common (virtual) base of Test and Sports.
// Result inherits from both Test and Sports, so without 'virtual'
// it would contain two copies of Student (the diamond problem).
//
//            Student
//             ^   ^
//     Test ---+   +--- Sports
//       ^             ^
//       +---- Result -+
class Student {
protected:
    int rollNo;
 
public:
    Student(int r) : rollNo(r) {
        cout << "  Student constructor called" << endl;
    }
    ~Student() { cout << "  Student destructor called" << endl; }
};
 
class Test : virtual public Student {
protected:
    float marks;
 
public:
    Test(int r, float m) : Student(r), marks(m) {
        cout << "  Test constructor called" << endl;
    }
    ~Test() { cout << "  Test destructor called" << endl; }
};
 
class Sports : virtual public Student {
protected:
    float score;
 
public:
    Sports(int r, float s) : Student(r), score(s) {
        cout << "  Sports constructor called" << endl;
    }
    ~Sports() { cout << "  Sports destructor called" << endl; }
};
 
class Result : public Test, public Sports {
public:
    // The most derived class constructs the virtual base Student directly (only once).
    Result(int r, float m, float s) : Student(r), Test(r, m), Sports(r, s) {
        cout << "  Result constructor called" << endl;
    }
    void display() const {
        cout << "  Roll No: " << rollNo << endl;          // no ambiguity: one copy of Student
        cout << "  Test marks: " << marks << ", Sports score: " << score << endl;
        cout << "  Total: " << marks + score << endl;
    }
    ~Result() { cout << "  Result destructor called" << endl; }
};
 
int main() {
    string pName, subject;
    int papers, roll;
    float marks, score;
 
    cout << "Enter professor name, subject, number of papers: ";
    cin >> pName >> subject >> papers;
    cout << "Enter student roll no, test marks, sports score: ";
    cin >> roll >> marks >> score;
 
    cout << fixed << setprecision(1);
 
    cout << "\n=== 4. Multiple Inheritance (Teacher + Researcher -> Professor) ===" << endl;
    {
        Professor p(pName, subject, papers);
        p.display();
    }
 
    cout << "\n=== 5. Hybrid Inheritance (virtual base class) ===" << endl;
    {
        Result res(roll, marks, score);
        res.display();
    }
 
    return 0;
}
 