#include <stdio.h> 
#include "file_group/file_group_writer.h"
#include "file_group/file_group_reader.h"

using namespace tis;

void test_writer() {
#define WRITE(writer, value, len) do { \
    if (writer->write(value, len)) { \
        printf("write error\n"); \
    } \
} while(0);
    FileGroupWriter* writer = new FileGroupWriter;
    if (writer->init("./", "test", 10)) {
        printf("writer init error\n"); 
        return;
    }
    uint64_t value = 1;
    WRITE(writer, &value, sizeof(value));
    value = 2;
    WRITE(writer, &value, sizeof(value));
    value = 3;
    WRITE(writer, &value, sizeof(value));
    value = 4;
    WRITE(writer, &value, sizeof(value));
    if (writer->finish()) {
        printf("writer finish error\n"); 
        return;
    }
}

void test_reader() {
#define READ(reader, fileno, off) do { \
    const int* value = (const int*)reader->read(fileno, off); \
    if (value) { \
        printf("read: fileno[%d] off[%d] value[%d]\n", fileno, off, *value); \
    } else { \
        printf("read: fileno[%d] off[%d] NULL\n", fileno, off); \
    } \
} while(0);
    FileGroupReader* reader = new FileGroupReader; 
    int ret = reader->load("./", "test");
    if (ret) {
        printf("reader load error, ret[%d]\n", ret); 
        return;
    }
    READ(reader, 0, 0);
    READ(reader, 0, 8);
    READ(reader, 0, 17);
    READ(reader, 1, 0);
    READ(reader, 1, 8);
    READ(reader, 2, 8);
    reader->close();
}

int main(int argc, char** argv) {
    test_writer();
    test_reader();
    return 0;
}
