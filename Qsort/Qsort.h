#ifndef QSORT_H
#define QSORT_H

#include "../Stuff.h"

int my_qsort( void* array, int nElem, size_t szElem, int ( *Comp )( const void*, const void* ) );

#endif // QSORT_H
