#ifndef __FILE_GROUP_WRITER_
#define __FILE_GROUP_WRITER_

#include <stdint.h>
#include <string>

namespace tis {

class FileGroupWriter {
public:
    static const uint32_t DEFAULT_MAX_LEN = 1024 * 1024 * 128; 

public:
    FileGroupWriter() {}
    virtual ~FileGroupWriter();

public:
    int init(const char* dir, 
             const char* prefix, 
             uint32_t max_len = DEFAULT_MAX_LEN);
    int write(const void* data, 
              int len,
              int* file_no = NULL,
              uint32_t* off = NULL,
              bool force_not_create = false);
    int finish();

private:
    std::string _dir;
    std::string _prefix;
    uint32_t _max_len;
    uint32_t _current_len;
    int _file_no;
    FILE* _fp;
};

}

#endif
