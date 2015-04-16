#ifndef __STRING_HELPER_H_
#define __STRING_HELPER_H_

namespace lj {
namespace StringHelper {

char* rtrim(char* s);
char* ltrim(char* s);
char* trim(char* s);
inline int next_term_utf8(const char* str);

}
}

#endif // __STRING_HELPER_H_
