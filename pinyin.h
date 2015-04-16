#ifndef __PINYIN_H_
#define __PINYIN_H_
#include "stdlib.h"

namespace tis {

typedef struct py_info_t {
    int num;
    char** ptrs;

    py_info_t() { ptrs = NULL;}

    ~py_info_t() {
        if (num > 0 && ptrs) {
            free(ptrs[0]); 
            free(ptrs);
        } 
    }
} py_info_t;

void init_pinyin ();
const py_info_t* pinyin_utf8(char* s);


}
#endif // __PINYIN_H_
