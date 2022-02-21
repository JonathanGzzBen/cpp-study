#include <stdio.h>

#ifdef _WIN32

#include <stdlib.h>

#endif

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    puts("Como se me antoja escribir año en vez de ano.");
    return 0;
}