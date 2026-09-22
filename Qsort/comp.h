#ifndef COMP_H
#define COMP_H

int cmpstringDOWN( const void* a, const void* b );
int cmpintUP( const void* a, const void* b );
int cmpcharUP( const void* a, const void* b );
int cmpshortUP( const void* a, const void* b );
int cmplonglongUP( const void* a, const void* b );
int cmpfloatUP( const void* a, const void* b );
int cmpdoubleUP( const void* a, const void* b );
int MC_PUSHKIN( const void* a, const void* b );
int MC_PUSHKIN_frag( const void* a, const void* b );
int cmpstringDOWN_frag( const void* a, const void* b );

#endif // COMP_H
