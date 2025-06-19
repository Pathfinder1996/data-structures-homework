#ifndef AV_LIST_H
#define AV_LIST_H
#include <cstddef>

void* operator new  (std::size_t) noexcept;
void  operator delete(void*) noexcept;
void* operator new[]  (std::size_t) noexcept;
void  operator delete[](void*) noexcept;

#endif
