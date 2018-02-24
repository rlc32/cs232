/* Vec.cpp defines the methods for Vec, a simple vector class.
 * Student Name: Alastair Van Maren
 * Date: February 23, 2016
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 * Member 1: Alastair Van Maren, wrote operator[] (read version), operator!=(), readFrom(), operator-()
 * Member 2: Ryan Johnson, wrote operator[] (write version), writeTo, operator+(), operator*()
 */
 
#include "Vec.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

Vec::Vec() {
mySize = 0 ;
myArray = NULL ;
}

Vec::Vec(unsigned size) {
mySize = size;
myArray = new Item[size];
for (unsigned i = 0; i < size; i++) {
myArray[i] = 0;
}
}

Vec::Vec(const Vec& original) {
mySize = original.mySize;
if (original.mySize > 0) {
myArray = new Item[mySize];
for (unsigned i = 0; i < mySize; i++) {
myArray[i] = original.myArray[i];
}
} else {
myArray = NULL;
}
}

Vec& Vec::operator=(const Vec& original) {
if (this != &original) {
if (mySize != original.mySize) {
if (mySize > 0) {
delete[] myArray;
myArray = NULL;
}
if (original.mySize > 0) {
myArray = new Item[original.mySize];
}
mySize = original.mySize;
}
}
for (unsigned i = 0; i < mySize; i++) {
myArray[i] = original.myArray[i];
}
return *this;
}

void Vec::setItem(unsigned index, const Item& it) {
if (index >= mySize) {
throw range_error("That index doesn't exist in this Vec");
} else {
myArray[index] = it;
}
}

Item Vec::getItem(unsigned index) const {
if (index >= mySize) {
throw range_error("That index doesn't exist in this Vec");
} else {
return myArray[index] ;
}
}

void Vec::setSize(unsigned newSize) {
if (mySize != newSize) {
if (newSize == 0) {
delete[] myArray;
mySize = 0;
myArray = NULL;
} else {
Item* newArray = new Item[newSize]();
if (mySize < newSize) {
for (unsigned i = 0; i < mySize; i++) {
newArray[i] = myArray[i];
}
} else {
for (unsigned i = 0; i < newSize; i++) {
newArray[i] = myArray[i];
}
}
mySize = newSize;
delete[] myArray;
myArray = newArray;
}
}
}

bool Vec::operator==(const Vec& v2) {
if (mySize == v2.mySize) {
for (unsigned i = 0; i < mySize; i++) {
if (myArray[i] != v2.myArray[i]) {
return false;
}
}
return true;
} else {
return false;
}
}

void Vec::writeTo(ostream& out) const {
for (unsigned i = 0; i < mySize; i++) {
out << myArray[i] << "\t" << flush;
}
}

void Vec::readFrom(istream& in) {
for (unsigned i = 0; i < mySize; i++) {
in >> myArray[i] ;
}
}
/* The definition of the change function of the [ ] operator
 * Postcondition: the value at the given index is changed
 */
void Vec::operator[](unsigned index) {
*this = myArray[index] ;
}

/* The definition of the retrieval function of the [ ] operator
 * Postcondition: the value at the given index is returned
 */
Item& Vec::operator[](unsigned index) const {
return myArray[index] ;
}

/* The definition of the != (inequality) operator
 * Parameters: two Vecs
 * Returns: boolean true or false
 */
bool Vec::operator!=(const Vec& v1) {
if (mySize != v1.mySize) {
return true;
} else
for (unsigned i = 0; i < mySize; i++) {
if (myArray[i] != v1.myArray[i]) {
return true;
}
}
return false;
}

/* The definition of addition for the Vec class
 * Parameters: two Vecs of the same size
 * Returns: a Vec of the sums of the two parameters
 */
Vec Vec::operator+(Vec& v1) {
if (mySize == v1.mySize) {
for (unsigned i = 0; i < mySize; i++) {
v1.myArray[i] = myArray[i] + v1.myArray[i] ;
}
} else {
throw invalid_argument("Attempted operation on Vecs of different sizes") ;
}
return v1 ;
}

/* The definition of subtraction for the Vec class
 * Parameters: two Vecs of the same size
 * Returns: a Vec of the subtracted values of the two parameters
 */
Vec Vec::operator-(Vec& v1) {

if (mySize == v1.mySize) {
for (unsigned i = 0; i < mySize; i++) {
v1.myArray[i] = myArray[i] - v1.myArray[i];
}
} else {
throw invalid_argument(
"Attempted operation on Vecs of different sizes");
}
return v1;
}

/* The definition of multiplication for the Vec class
 * Parameters: two Vecs of the same size
 * Returns: the sum of the multiplication of each corresponding element of the parameters
 */
double Vec::operator*(Vec& v1) {
if (mySize == v1.mySize) {
for (unsigned i = 0; i < mySize; i++) {
v1.myArray[i] = myArray[i] * v1.myArray[i];
}
} else {
throw invalid_argument(
"Attempted operation on Vecs of different sizes");
}
double dProd = 0;
for (unsigned i = 0; i < mySize; i++) {
dProd += v1.myArray[i];
}
return dProd;
}

/* Preconditions: a file in the proper format, a Vec
 * Postcondition: the Vec contains the numbers specified in the file
 */
void Vec::readFrom(string fileName) {
ifstream infile ;
infile.open(fileName.c_str()) ;
infile >> mySize ;
if (myArray == NULL) {
myArray = new Item[mySize] ;
}
for (unsigned i = 0; i < mySize; i++) {
infile >> myArray[i] ;
}
infile.close() ;
}
/* Preconditions: a Vec, a file that can be written into
 * Postcondition: the values from the Vec have been copied into the file
 */
void Vec::writeTo(string fileName) {
ofstream outfile ;
outfile.open(fileName.c_str()) ;
outfile << mySize << endl ;
if (myArray == NULL) {
myArray = new Item[mySize] ;
}
for (unsigned i = 0; i < mySize; i++) {
outfile << myArray[i] << endl ;
}
outfile.close() ;
}

Vec::~Vec() {
delete [] myArray ;
myArray = NULL ;
mySize = 0 ;
}