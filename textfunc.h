#ifndef TEXTFUNC_H
#define TEXTFUNC_H

struct frag
{
    char* begin;
    char* end;
};

struct poem
{
    char* txt;
    uint64_t cpp;
};

int ReadText_Separated( char **ind, size_t szInd, const char* filename );
struct poem ReadText_Buff( const char* filename );
struct frag* Divide( struct poem text );
int CountLines( struct poem text );
void puts_my( const char* a, FILE* ostream );
void Print_frag( struct frag* lines, uint64_t size, FILE* ostream );

#endif // TEXTFUNC_H
