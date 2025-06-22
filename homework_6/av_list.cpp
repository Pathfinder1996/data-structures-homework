#include <iostream>
#include <cstdlib>
#include "av_list.h"
#include "Polynomial.h"
#include "ChainNode.h"

// Overloading Global new operator
void av_init(Chain<Term> av, int num) {
    for (int i = 0; i < num; i++) {
        Term *e=new Term;
        av.InsertBack(*e);
    }
}

void* operator new(size_t sz)
{
    void* m = malloc(sz);
    std::cout << "User Defined :: Operator new" << std::endl;

    return m;
}
// Overloading Global delete operator
void operator delete(void* m)
{
    std::cout << "User Defined :: Operator delete" << std::endl;
    free(m);
}
// Overloading Global new[] operator
void* operator new[](size_t sz)
{
    std::cout << "User Defined :: Operator new []" << std::endl;
    void* m = malloc(sz);
    return m;
}
// Overloading Global delete[] operator
void operator delete[](void* m)
{
    std::cout << "User Defined :: Operator delete[]" << std::endl;
    free(m);
}