#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

file_info read_entire_file(const char* path)
{
    
    file_info result = {};
    FILE* file = fopen(path, "rb");
    if(!file)
    {
        printf("cannot find file (%s)\n", path);
        return result;
    }
    
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = (char*)malloc(size+1);
    fread(content, 1, size, file);
    fclose(file);
    content[size] = 0;

    result.content = content;
    result.size = size;
    return result;
}
