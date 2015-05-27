#include "string_helper.h"
#include "string.h"

namespace tis{
namespace StringHelper {

char* rtrim(char* s) {
    int len = strlen(s);
    while (true) {
        if (len <= 0) {
            break; 
        }
        char c = s[len - 1]; 
        if (' ' != c 
                && '\r' != c 
                && '\n' != c
                && '\t' != c
                && '\v' != c) {
            break;
        }
        --len;
    }
    s[len] = '\0';
    return s;
}

char* ltrim(char* s) {
    int i = 0;
    while (true) {
        char c = s[i];
        if ('\0' == c) {
            break; 
        }
        if (' ' != c
                && '\r' != c
                && '\n' != c
                && '\t' != c
                && '\v' != c) { 
            break;
        }
        ++i; 
    }
    if (0 == i) {
        return s;
    }
    int p = i;
    while (true) {
        char c = s[p];
        if ('\0' == c) {
            s[p - i] = c;
            break; 
        } else {
            s[p - i] = c;
            ++p;
        }
    }
    return s;
}

char* trim(char* s) {
    rtrim(s);
    ltrim(s);
    return s;
}

void split(const char* s, 
           char sep, 
           std::vector<std::string>* list,
           bool allow_empty) {
    if (!s || !list) return;
    const char* begin = s;
    const char* end = NULL;
    list->clear();
    while (true) {
        end = strchr(begin, sep);
        if (end) {
            if (end - begin > 0 || allow_empty) {
                list->push_back(std::string(begin, end - begin)); 
            }
        } else {
            if ('\0' != begin[0] || allow_empty) {
                list->push_back(std::string(begin)); 
            }
            break;
        }
        begin = end + 1;
    }
}

int next_term_utf8(const char* str) {
    unsigned char *strIn = (unsigned char *)str;

    if (str == NULL) {
        return -1;
    }
    if ('\0' == *str) {
        return 0; 
    }


    /* 增加的判断分支主要是考虑了unicode中的情况，过滤了一些不应该出现的区域,
     * 因为字节数多的不能比少的unicode值小*/
    /* 7 0xxxxxxx */
    if (strIn[0] < 0x80) {
        return 1;
    }
    /* 11 110xxxxx 10xxxxxx */
    if (strIn[0] >= 0xC2 && strIn[0] < 0xE0 && strIn[1] >> 6 == 2) {
        return 2;
    }
    /* 16 1110xxxx 10xxxxxx 10xxxxxx */
    if (strIn[0] >> 4 == 14 && strIn[1] >> 6 == 2 && strIn[2] >> 6 == 2 && (strIn[0] > 0xE0 || strIn[1] >= 0xA0)) {
        return 3;
    }
    /* 21 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if (strIn[0] >> 3 == 30 && strIn[1] >> 6 == 2 && strIn [2] >> 6 == 2 && strIn[3] >> 6 == 2 && (strIn[0] > 0xF0 || strIn[1] >= 0x90)) {
        return 4;
    }
    /* 26 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if (strIn[0] >> 2 == 62 && strIn[1] >> 6 == 2 && strIn [2] >> 6 == 2 && strIn[3] >> 6 == 2 && strIn[4] >> 6 == 2 && (strIn[0] > 0xF8 || strIn[1] >= 0x88)) {
        return 5;
    }
    /* 31 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if (strIn[0] >> 1 == 126 && strIn[1] >> 6 == 2 && strIn [2] >> 6 == 2 && strIn[3] >> 6 == 2 && strIn[4] >> 6 == 2 && strIn[5] >> 6 == 2 && (strIn[0] > 0xFC || strIn[1] >= 0x84)) {
        return 6;
    }
    return 0;
}


}
}
