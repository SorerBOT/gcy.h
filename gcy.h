#ifndef GCY_H
#define GCY_H

#include <stdlib.h>
#ifdef GCY_MODE

typedef struct
{
    size_t size;
    char* file;
    int line;
    void* ptr;
} GCY_Allocation;
typedef struct GCY_AllocationsList
{
    GCY_Allocation* alloc;
    struct GCY_AllocationsList* next;
} GCY_AllocationsList;

void* gcy_malloc(size_t size, char* file, int line);
void gcy_free(void* ptr);
void gcy_print_errors();

#define GCY_MALLOC(size) gcy_malloc((size), __FILE__, __LINE__)
#define GCY_FREE(ptr) gcy_free((ptr))
#else /* GCY_MODE */
#define GCY_MALLOC(size) malloc((size))
#define GCY_FREE(ptr) free((ptr))
#endif
#endif

#ifdef GCY_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>


GCY_AllocationsList* allocList = NULL;

void* gcy_malloc(size_t size, char* file, int line)
{
    void* ptr = malloc(size);
    if (ptr == NULL)
    {
        fprintf(stderr, "Error: malloc");
        exit(EXIT_FAILURE);
    }

    GCY_AllocationsList* root_new = (GCY_AllocationsList*)malloc(sizeof(GCY_AllocationsList));
    if (root_new == NULL)
    {
        fprintf(stderr, "Error: malloc in Garbage-Collectyour library allocation");
        exit(EXIT_FAILURE);
    }

    root_new->alloc = (GCY_Allocation*)malloc(sizeof(GCY_Allocation));
    if (root_new->alloc == NULL)
    {
        fprintf(stderr, "Error: malloc in Garbage-Collectyour library allocation");
        exit(EXIT_FAILURE);
    }
    *root_new->alloc = (GCY_Allocation)
    {
        .size = size,
        .file = file,
        .line = line,
        .ptr  = ptr
    };
    root_new->next = allocList;
    allocList = root_new;

    return ptr;
}

#endif /* GCY_IMPLEMENTATION */
