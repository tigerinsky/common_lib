
#include "file_group_writer.h"
#include <stdio.h> 
#include <string.h>

namespace tis {

static FILE* get_file(const char* dir, const char* prefix, int file_no) {
    char path[512];
    snprintf(path, 511, "%s/%s.%d", dir, prefix, file_no);
    return fopen(path, "w");
}

static FILE* get_n_file(const char* dir, const char* prefix) {
    char path[512];
    snprintf(path, 511, "%s/%s.n", dir, prefix);
    return fopen(path, "w");
}

FileGroupWriter::~FileGroupWriter() {
    if (_fp) {
        (void)fclose(_fp); 
    }
}

int FileGroupWriter::init(const char* dir, const char* prefix, uint32_t max_len) {
    _dir = dir;   
    _prefix = prefix;
    _max_len = max_len;

    _fp = get_file(_dir.c_str(), _prefix.c_str(), 0);
    if (!_fp) {
        return 1; 
    }
    _current_len = 0;
    _file_no = 0;
    return 0;
}

int FileGroupWriter::write(const void* data, int len) {
    if (_current_len > _max_len) {
        (void)fclose(_fp); 
        _fp = get_file(_dir.c_str(), _prefix.c_str(), _file_no + 1);
        if (!_fp) {
            return 1; 
        }
        _current_len = 0;
        ++_file_no;
    }
    if (1 != fwrite(data, len, 1, _fp)) {
        return 2; 
    }
    _current_len += len; 
    return 0;
}

int FileGroupWriter::finish() {
    (void) fclose(_fp);
    _fp = NULL;
    FILE* fp = get_n_file(_dir.c_str(), _prefix.c_str()); 
    if (!fp) {
        return 1; 
    }
    char buff[512];
    snprintf(buff, 511, "%d", _file_no + 1);
    if (1 != fwrite(buff, strlen(buff), 1, fp)) {
        return 2; 
    } 
    (void) fclose(fp);
    return 0;
}

}
