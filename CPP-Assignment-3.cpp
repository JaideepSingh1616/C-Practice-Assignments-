#include <iostream>
using namespace std;

class Complex {
private:
    int real;
    int imag;

public:
    // Default Constructor
    Complex() {
        real = 0;
        imag = 0;
    }

    // Parameterized Constructor
    Complex(int r, int i) {
        real = r;
        imag = i;
    }

    // Overloading the '+' operator
    Complex operator+(Complex obj) {
        Complex temp;
        // Adding the real and imaginary parts separately
        temp.real = real + obj.real;
        temp.imag = imag + obj.imag;
        return temp;
    }

    // Function to display the complex number in "a+bi" format
    void display() {
        if (imag >= 0) {
            cout << real << "+" << imag << "i" << endl;
        } else {
            // If imag is negative, it already includes the minus sign (e.g., 7-3i)
            cout << real << imag << "i" << endl; 
        }
    }
};

int main() {
    int r1, i1, r2, i2;

    // Taking user input for the first complex number
    cout << "Enter real and imaginary part of first complex number: ";
    cin >> r1 >> i1;
    Complex c1(r1, i1); // Using parameterized constructor

    // Taking user input for the second complex number
    cout << "Enter real and imaginary part of second complex number: ";
    cin >> r2 >> i2;
    Complex c2(r2, i2); // Using parameterized constructor

    // Creating an empty object using the default constructor to store the result
    Complex c3;
    
    // Performing addition using the overloaded '+' operator
    c3 = c1 + c2;

    // Displaying the final outputs
    cout << "First Complex Number: ";
    c1.display();
    
    cout << "Second Complex Number: ";
    c2.display();
    
    cout << "Addition: ";
    c3.display();

    return 0;
}