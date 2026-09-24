# Onegin
## About
This repo provides users with ability to sort text either from .txt file, or any other streams.

### Abilities
Also in the file you can find other essential functions for

1. Debugging in 'Debug.cpp' or 'Debug.h'

2. Quick sort in 'Qsort' with clear debugging prints, which provide user with understanding of the whole sorting process.

3. Sort text, starting with the beginning of lines with
> int cmpstringDOWN( const void* a, const void* b );

4. Sort text, starting with the end of lines with
> int MC_PUSHKIN( const void* a, const void* b );

### Terminal commands

1. -input 'filename' Changes input stream to mentioned file

2. -output 'filename' Changes output stream to mentioned file

## Tech

1. MC_PUSHKIN function and MC_PUSHKIN_frag functions compare lines, starting from their end. ( Compare only letters and ignore other symbols )

2. cmpstringDOWN and cmpstringDOWN_frag functions compare lines, starting from their beginning ( Also they cmp only letters and ignore other symbols )

3. 'Versus' files contains some funny outputs and doesn't carry much meaning

4. 'pushkin.txt' and 'output.txt' are original files for input and output respectively

5. Qsort folder contains custom qsort function and some essential comparators

### To learn more about included functions you can check Doxygen - generated documentation in Github-pages




