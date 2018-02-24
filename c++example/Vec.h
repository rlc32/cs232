#ifndef VEC_H_
#define VEC_H_

#include <iostream>
using namespace std;

typedef double Item;

class Vec {
public:
Vec();
virtual ~Vec();
Vec(unsigned size) ;
Vec(const Vec& original) ;
Vec& operator=(const Vec& original) ;
unsigned getSize() const { return mySize ; } ;
void setItem(unsigned index, const Item& it) ;
Item getItem(unsigned index) const ;
void setSize(unsigned newSize) ;
bool operator==(const Vec& v2) ;
void writeTo(ostream& out) const ;
void readFrom(istream& in) ;
void operator[](unsigned index);
Item& operator[](unsigned index) const;
bool operator!=(const Vec& v1) ;
Vec operator+(Vec& v1) ;
Vec operator-(Vec& v1) ;
double operator*(Vec& v1) ;
void readFrom(string fileName) ;
void writeTo(string fileName) ;
 
private:
unsigned mySize ;
Item* myArray ;
friend class VecTester ;
};