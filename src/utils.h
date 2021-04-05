#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

struct file_info
{
    char* content;
    uint32_t size;
    
};

file_info read_entire_file(const char* path);

#endif //UTILS_H
