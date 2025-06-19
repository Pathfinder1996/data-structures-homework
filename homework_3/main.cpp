/*
Data Structures Homework 3
M11212913 Sheng-Yen Dai, 2025/03/28
*/

#include "Polynomial.h"
#include <iomanip>
int main() {
Polynomial a, b, c, d;
cout << "(1) Input Data\n";

a.getdata('A');
b.getdata('B');	

// a.set(1, 1); //1 x^1
// a.set(2, 2); //2 x^2
// a.name = 'A';
// b.set(5, 0); //5 x^0
// b.set(3, 3); //3 x^3
// b.set(4, 4);   // 4 x^4
// b.name = 'B';

cout << "\n(2) Perform Polynomial Operations (+, -, *):\n";
c = a + b;   //   operator overloading of "+"
cout << setw(5) << a.name << "+" << b.name << "=";
cout << a << "+" << b << "=" << c << endl;    // operator overloading of "+"
c = a-b;      //  operator overloading of "-", a.minus(b)
cout << setw(5) << a.name << "-" << b.name << "=";
cout << a << "-" << b << "=" << c << endl;    // print out the c polynomial

c = a * b; // operator overloading of "*" or c=a.times(b)
cout << setw(5) << a.name << "*" << b.name << "=";
cout << a << "*" << b << "=" << c << endl ;  //  operator overloading for output polynomial

cout << "\n(3) Perform Derivations D'(x)\n";
d = c.differentiate().differentiate();  d.name = 'D';
cout << "    Differentiate "<< d.name <<"(x) = " << c << " two times lead to: \n"
<< setw(5) << d.name<<"''(x) = " << d << endl;   // operator overloading <<

int x = 2; cout << "\n(4) Setting x = " << x << endl;
cout << "    Evaluate the polynomial C(x) = " << c
		<< " with x=" << x << endl
		<< "    i.e., C("<<x<<"), lead to a numerical value : " 
		<< c(x) << endl; // evaluate the polynomial with x=2 by horner's method, 
						// i.e., a.evaluate(x=2) is replace with a(2)
cin.get();   // wait for you to press a key to finish the program

   return 0;
}
