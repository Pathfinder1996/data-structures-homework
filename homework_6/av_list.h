#pragma once
#include <iostream>
using namespace std;
extern int debug;

void* operator new(size_t sz) {
	void* m = malloc(sz);
	if (!m) throw std::bad_alloc(); // <== throw if malloc fails
	if (debug) std::cout << "\nUser Defined :: Operator new" << std::endl;
	return m;
}


// Overloading Global delete operator
void operator delete(void* m) {
	if(debug) std::cout << "\nUser Defined :: Operator delete" << std::endl;
	free(m);
}
// Overloading Global new[] operator
void* operator new[](size_t sz) {
	if(debug) std::cout << "User Defined :: Operator new []" << std::endl;
	void* m = malloc(sz);
	return m;
}
// Overloading Global delete[] operator
void operator delete[](void* m) {
	if(debug) std::cout << "User Defined :: Operator delete[]" << std::endl;
	free(m);
}
