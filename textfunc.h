#ifndef TEXTFUNC_H
#define TEXTFUNC_H

struct poem
{
    char* txt;
    uint64_t cpp;
};

int ReadText_Separated( char **ind, size_t szInd, const char* filename );
struct poem ReadText_Buff( const char* filename );
struct poem* Sort( struct poem text );
int CountLines( struct poem text );

#endif // TEXTFUNC_H
