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

int ReadText_Separated( const char **ind, const size_t szInd, const char* filename );
struct poem ReadText_Buff( const int istream, const char* filename );
struct frag* Divide( const struct poem text );
int CountLines( const struct poem text );
void puts_my( const char* a, FILE* ostream );
void Print_poem( const struct frag* lines, const uint64_t size, FILE* ostream );

#endif // TEXTFUNC_H
