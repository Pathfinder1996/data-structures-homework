/*
Data Structures Homework 2
M11212913 Sheng-Yen Dai, 2025/03/19
*/

#include "complex.h"
using namespace std;

// CONSTRUCTOR
complex::complex(const complex &c) {
           this->real=c.real;
           this->imag=c.imag;
}

// operator overloading for '=' , i.e., copy functionD
complex complex::operator=(const complex &c) {
            real=c.real;
            imag=c.imag;			  
        return *this;
}

/*
if C1 = a + bi, C2 = c + di
then C1 + C2 = (a + c) + (b + d)i
*/

complex complex::operator +(const complex &c) {
	complex tmp, tmp1 = *this, tmp2(c);
	    cout << "\n performing C1 + C2 =" << tmp1 << "+" << tmp2 << " =";
           tmp.real=this->real+c.real;
           tmp.imag=this->imag+c.imag;
        return tmp;
}

/*
if C1 = a + bi, C2 = c + di
then C1 - C2 = (a - c) + (b - d)i
*/
complex complex::operator -(const complex c) {
	complex tmp, tmp1 = *this, tmp2 = c;
	cout << "\n performing C1 - C2 =" << tmp1 << "-" << tmp2 << " =";

    tmp.real = this->real - c.real;
    tmp.imag = this->imag - c.imag;

    return tmp;
}

/*
if C1 = a + bi, C2 = c + di
then C1 * C2 = (a*c - b*d) + (a*d + b*c)i
*/
complex complex::operator *(const complex c) {
	complex tmp, tmp1 = *this, tmp2 = c;
	cout << "\n performing C1 * C2 =" << tmp1 << "*" << tmp2 << " =";

    tmp.real = (this->real * c.real) - (this->imag * c.imag);
    tmp.imag = (this->real * c.imag) + (this->imag * c.real);

    return tmp;
}

/*
if C1 = a + bi, C2 = c + di
then C1 / C2 = ((a*c + b*d) + (b*c - a*d)i) / (c^2 + d^2)
*/
complex complex::operator /(const complex c) {
	complex tmp, tmp1 = *this, tmp2 = c;
    float div;
	cout << "\n performing C1 / C2 =" << tmp1 << "/" << tmp2 << " =";

	div = (c.real * c.real) + (c.imag * c.imag);

    tmp.real = ((this->real * c.real) + (this->imag * c.imag)) / div;
    tmp.imag = ((this->imag * c.real) - (this->real * c.imag)) / div;

    return tmp;
}

/*
if C = a + bi
then conjugate(C) = a - bi
*/
complex complex::getconjugate()
{
	complex tmp;
	cout << "\n performing C2 = conjugate(C1) =" << endl;
    
    tmp.real = this->real;
    tmp.imag = -(this->imag);

    return tmp;
}

/*
if C = a + bi
then reciprocal(C) = (a - bi) / (a^2 + b^2)
*/
complex complex::getreciprocal(){
	// Performing C^(-1)
	complex t;

	float div = 0;
    div = ((this->real * this->real) + (this->imag * this->imag));

    t.real = this->real / div;
    t.imag = -(this->imag / div);

    return t;
}

/*
if C = a + bi
then |C| = sqrt(a^2 + b^2)
*/
float complex::getmodulus()
{
	complex tmp = *this;
	cout << "\n performing |C| =" <<"|" <<tmp <<"| = ";

	float z=0;

    z = sqrt(((this->real * this->real) + (this->imag * this->imag)));

    return z;
}

// Set real and imaginary parts
void complex::setdata(float r,float i) {
       real=r;
       imag=i;
}

// Input real and imaginary parts from user
void complex::getdata() {
    string str;
       cout<<" Enter Real:";
       cin >> this->real;   cout << this->real; 
       cout<<"\n Enter Imaginary:";
       cin >> this->imag;   cout << this->imag <<endl; getline(cin, str);
}

// Get real
float complex::getreal() {
       return real;
}

// Get imaginary
float complex::getimaginary() {
       return imag;
}

// Check if two complex numbers are equal
bool complex::operator ==(const complex & c) {
       return (real==c.real)&&(imag==c.imag) ? 1 : 0;
}

// Output operator overloading
ostream& operator<<(ostream &s,const complex &c){
       s<<" ("<<c.real<<setiosflags(ios::showpos)
       <<c.imag<<"i"<<") "<<resetiosflags(ios::showpos);
       return s;
}
