
#include "string_helper.h"

void test_split() {
    char* s = "\t1\t\t2 \t22\t";
    std::vector<std::string> list;
    tis::StringHelper::split(s, '\t', &list);
    for (auto ite = list.begin(); ite != list.end(); ++ite) {
        printf("[%s]\n", ite->c_str()); 
    }
}

int main (int argc, char** argv) {
    test_split();
    return 0;
}
