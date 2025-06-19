#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <ostream>

using namespace std;

class complex
{
   public:
      float real;
      float imag;
   public:
      complex(float r=0,float im=0):real(r),imag(im) { }
      complex(const complex&);
      complex operator +(const complex&);
      complex operator -(const complex);
      complex operator *(const complex);
      complex operator /(const complex);
      complex getconjugate();
      complex getreciprocal();
      float getmodulus();
      void setdata(float,float);
      void getdata();
      float getreal();
      float getimaginary();
      bool operator ==(const complex&);
      complex operator =(const complex&);
      friend ostream & operator<<(ostream &s, const complex &c);
};


