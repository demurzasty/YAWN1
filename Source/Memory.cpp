#include <YAWN/Memory.hpp>
#include <YAWN/Error.hpp>

#include <stdlib.h>

using namespace YAWN;

void* Memory::Allocate(size_t size, size_t count) {
    void* data = malloc(size * count);
    Assert(data, "Not enough memory.");
    return data;
}

void* Memory::Reallocate(void* data, size_t size, size_t count) {
    void* newData = realloc(data, size * count);
    Assert(newData, "Not enough memory.");
    return newData;
}

void Memory::Deallocate(void* data) {
    free(data);
}