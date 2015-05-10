#ifndef __STRING_HELPER_H_
#define __STRING_HELPER_H_

#include <string> 
#include <vector>

namespace tis {
namespace StringHelper {

char* rtrim(char* s);
char* ltrim(char* s);
char* trim(char* s);

void split(const char* s, 
           char sep, 
           std::vector<std::string>* list, 
           bool allow_empty=true);

inline int next_term_utf8(const char* str);

}
}

#endif // __STRING_HELPER_H_
