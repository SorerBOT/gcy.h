#include <string.h>
#include <stdio.h>
#define GCY_MODE 1
#define GCY_IMPLEMENTATION 1
#include "gcy.h"

int main()
{
    char* my_str = "hello world\n";
    char* ptr = (char*)GCY_MALLOC(strlen(my_str) * sizeof(char));
    memcpy(ptr, my_str, strlen(my_str));
}
