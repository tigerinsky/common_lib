#ifndef __FILE_GROUP_READER_
#define __FILE_GROUP_READER_

#include <stdint.h>
#include <string>

namespace tis {

struct file_t;

class FileGroupReader {
public:
    FileGroupReader() {}
    virtual ~FileGroupReader() {}

public:
    int load(const char* dir, const char* prefix); 
    const void* read(uint32_t file_no, uint32_t off);
    void close();

public:
    const char* get_dir() { return _dir.c_str(); }
    const char* get_prefix() { return _prefix.c_str(); }
    int get_file_num() { return _file_num; }

private:
    void __free();

    std::string _dir;
    std::string _prefix;
    int _file_num;
    file_t* _file_list;

};

}

#endif
