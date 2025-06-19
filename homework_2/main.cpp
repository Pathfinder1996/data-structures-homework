/*
Data Structures Homework 2
M11212913 Sheng-Yen Dai, 2025/03/19
*/

#include "complex.h" 
using namespace std;

int main()
{
	// program demo part 
	cout << "Demo Program ==============================\n";
	complex A(10.0f, -2.f);			// Calls Constructor
	cout << " A = " << A << endl;					// Calls the overloaded << operator
	complex B(-2);					// Calls Constructor
	complex C = A;                     // Calls Copy Constructor
	cout << " B = " << B << endl;
	cout << " C = " << C << endl;
	A = B;
	if (B == C)						// calls overloaded == operator
		cout << "\n B == C";
	else
		cout << "\n B != C";                             // calls overloaded = operator

	cout << C.getmodulus() << endl; // calls the getmodulus() function
	cout << "\n Performing C*C^(-1) = " << C << '*' << C.getreciprocal()
		<< '=' << C * C.getreciprocal() << endl;    // calls the receiprocal() function

		//  Your program starts here
	cout << "\nNow it's your turn =================================== \n";
	complex a, b;
	a.getdata();                     // Calls Getdata() to input complex numbers for b and c
	b.getdata();
	cout << a + b << endl;          // Calls overloaded + and <<
	cout << a - b << endl;          // Calls overloaded -  and << 
	cout << a * b << endl;          // calls overloaded *  and << 
	cout << a / b << endl;          // calls overloaded / and <<
	cout << (a + b) * (a - b) / C << endl;  // combine + - * / operations
	char ch = getchar();
	return 0;
}