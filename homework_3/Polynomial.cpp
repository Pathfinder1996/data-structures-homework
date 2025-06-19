#include "Polynomial.h"
#include <iomanip>

// get polynomial (coeff, order)s data
void Polynomial::getdata(char c) {
  float coef;
  int exp;
    name = c;
    while(cin >> coef) {
        cin >> exp;
        set(coef, exp);
    }
    cin.clear();
    cin.ignore(100, '\n');
    cout << setw(4)<< ' '<< "Polynomial " << c << ": " << *this << endl;
};

// polynomial addition
Polynomial Polynomial::operator+(Polynomial& b)
{
    Polynomial c;
    for (int i = 0; i <= this->deg; i++) c.coef[i] += this->coef[i];
    for (int i = 0; i <= b.deg; i++) c.coef[i] += b.coef[i];
    c.deg = c.degree();
    return c;
}

// Subtract polynomial b from this polynomial
Polynomial Polynomial::operator-(Polynomial& b)
{
    Polynomial C;

    int i;
    for (i = 0; i <= this->deg; i++) {
		C.coef[i] = C.coef[i] + this->coef[i];
    }
    for (i = 0; i <= b.deg; i++) {
		C.coef[i] = C.coef[i] - b.coef[i];
    }

	C.deg = C.degree();
    //c.set(1, 1);
    return C;
}

// Multiply two polynomials
Polynomial Polynomial::operator*(Polynomial& b)
{
    Polynomial c;

    int i, j;
	for (i = 0; i <= this->deg; i++) {
		for (j = 0; j <= b.deg; j++) {
			c.coef[i + j] = c.coef[i + j] + (this->coef[i] * b.coef[j]);
		}
	}

	c.deg = c.degree();
    //c.set(1, 1);
    return c;
}

// Return the derivative of the polynomial
Polynomial Polynomial::differentiate()
{
    Polynomial deriv;  // = new Polynomial ( 0, deg - 1 );

    int i;
    for (i = 1; i <= deg; i++) {
		deriv.coef[i - 1] = i * coef[i];
    }

	deriv.deg = deriv.degree();
    //deriv.set(1, 1);
    return deriv;
}

// Evaluate the polynomial using Horner's method
 // using C(2) instead of C.evaluate(2)
 // to evaluate the polynomial when x=2
float Polynomial::operator()(int x) {
    float p = 0.0;
       
    int i;
    for (i = deg; i >= 0; i--) {
        p = coef[i] + (x * p);
    }

    return p;
}

// use Horner's method to compute and return the polynomial evaluated at x
// wiki: https://en.wikipedia.org/wiki/Horner%27s_method
// https://www.youtube.com/watch?v=RGrmEWj38bsc
// return the polynomial evaluation with value x
   // or 
float Polynomial::evaluate(int x) {
    float p = 0.0;

	int i;
	for (i = deg; i >= 0; i--) {
		p = coef[i] + (x * p);
	}   

    return p;
}

// Overload << operator to print the polynomial
ostream& operator <<(ostream& os, Polynomial& s) {
    os << "(";
    for (int i = 99; i >= 0; i--) {
        if (s.coef[i] != 0) {
            if (s.coef[i] > 0) os << "+";
            os << s.coef[i] << "x^" << i ;
        }
    }
    os << ")";
    return os;
}

void Polynomial::set(float a, int b) { // function to set one term (a*x^b)
    coef[b] = a;
    if (b > deg) deg = b;
}
int Polynomial::degree() {  // find the highest degree of this polynomial
    int d = 0;
    for (int i = N - 1; i >= 0; i--) 
        if (coef[i] != 0) { d = i; i = -1; };
    return d;
}
