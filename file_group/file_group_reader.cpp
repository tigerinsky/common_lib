#include "file_group_reader.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "string_helper.h"

namespace tis {

typedef struct file_t {
    FILE* fp;
    uint64_t size;
    void* data;

    file_t() {
        fp = NULL; 
        size = 0;
        data = MAP_FAILED;
    }
} file_t;

static int read_num(const char* dir, const char* prefix) {
    char buf[1024];
    snprintf(buf, 1023, "%s/%s.n", dir, prefix);

    FILE* fp = fopen(buf, "r");
    if (!fp) {
        return -1; 
    }
    if (!fgets(buf, 1023, fp)) {
        return -2;
    }
    (void)fclose(fp);
    return atoi(buf);
}

static FILE* get_file(const char* dir, const char* prefix, int file_no) {
    char buf[1024];
    snprintf(buf, 1023, "%s/%s.%d", dir, prefix, file_no);
    return fopen(buf, "r");
}

void FileGroupReader::__free() {
    for (int i = 0; i < _file_num; ++i) {
        file_t* file = _file_list  + i;
        if (MAP_FAILED != file->data) {
            (void)munmap(file->data, file->size);
            file->data = MAP_FAILED;
            file->size = 0;
        } 
        if (file->fp) {
            (void)fclose(file->fp); 
            file->fp = NULL;
        }
    }
}

int FileGroupReader::load(const char* dir, const char* prefix) {
    int ret = -1;
    int num = read_num(dir, prefix);
    if (num < 0) {
        return 1; 
    }
    _file_num = num;

    _file_list = new(std::nothrow) file_t[num];
    if (!_file_list) {
        return 2; 
    }

    for (int i = 0; i < num; ++i) {
        FILE* fp = get_file(dir, prefix, i);
        if (!fp) {
            __free();
            return 2; 
        }
        _file_list[i].fp = fp;
    }


    struct stat st;
    for (int i = 0; i < num; ++i) {
        int fd = fileno(_file_list[i].fp);
        if (fstat(fd, &st)) {
            __free();
            return 3; 
        }
        void* s = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (MAP_FAILED == s) {
            __free();
            return 4; 
        }
        _file_list[i].size = st.st_size;
        _file_list[i].data = s;
    }

    _dir = dir;
    _prefix = prefix;
    return 0;
}

const void* FileGroupReader::read(uint32_t file_no, uint32_t off) {
    if (file_no >= _file_num || off > _file_list[file_no].size) {
        return NULL; 
    }
    file_t* file = _file_list + file_no;
    if (MAP_FAILED == file->data || off > file->size) {
        return NULL; 
    }
    return file->data + off;
}

void FileGroupReader::close() {
    __free();
}

}
