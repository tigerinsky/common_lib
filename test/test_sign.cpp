#include <string.h>
#include <stdio.h>
#include "hash/sign.h"


int main (int argc, const char** argv) {
    char str[] = "hello world";
    for (int i = 0; i < 10; ++i) {
        printf("%lld\n", sign64_str(str, strlen(str))); 
        str[0] = 'a' + i;
    }
    return 0;
}
