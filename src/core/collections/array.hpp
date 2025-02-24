#ifndef ST_ARRAY_H
#define ST_ARRAY_H
#include <stdio.h>
#include "core/core.hpp"

namespace starry {

/// man
#define ST_ARRAY_BUFFER_SIZE 256

/// statically sized list. for efficiency it uses the stack until it's bigger than 256, then it uses the heap.
template<typename T>
class Array {
private:
    T* heap_buf;
    T stack_buf[ST_ARRAY_BUFFER_SIZE];
public:
    /// if true, the array is on the heap. else, it's on the stack
    bool on_heap;
    /// how many items the array has.
    nint length;

    Array(nint size)
    {
        this->length = size;
        this->on_heap = size >= ST_ARRAY_BUFFER_SIZE;
        if (this->on_heap) {
            this->heap_buf = (T*)malloc(sizeof(T) * size);
        }
    }

    ~Array()
    {
        if (this->on_heap) {
            free(this->heap_buf);
        }
    }

    /// returns the item at the specified index
    T* at(nint idx)
    {
        if (idx >= this->length) {
            fprintf(stderr, "[CORE] Index out of range: index is %lu, length is %lu\n", idx, this->length);
            // a segfault is about to happen!
            fflush(stderr);
            return nullptr;
        }

        if (this->on_heap) {
            return &this->heap_buf[idx];
        }
        else {
            return &this->stack_buf[idx];
        }
    }

    /// returns the internal array
    T* get_buffer()
    {
        if (this->on_heap) return this->heap_buf;
        else return this->stack_buf;
    }
};

}


#endif // ST_ARRAY_H
