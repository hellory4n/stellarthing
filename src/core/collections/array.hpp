#ifndef ST_ARRAY_H
#define ST_ARRAY_H
#include <stdio.h>
#include <string.h>
#include "core/core.hpp"

namespace starry {

/// man
#define ST_ARRAY_BUFFER_SIZE 256

/// statically sized list. for efficiency it uses the stack until it's bigger than 256, then it uses the heap.
template<typename T>
class Array {
public:
    /// if true, the array is on the heap. else, it's on the stack
    bool on_heap;
    /// how many items the array has.
    nint length;
    T* __heap_buf = nullptr;
    T __stack_buf[ST_ARRAY_BUFFER_SIZE];

    Array(nint size)
    {
        this->length = size;
        this->on_heap = size >= ST_ARRAY_BUFFER_SIZE;
        if (this->on_heap) {
            this->__heap_buf = (T*)malloc(sizeof(T) * size);
            if (this->__heap_buf == nullptr) {
                fprintf(stderr, "[CORE] Memory allocation error; panicking\n");
                // memory is busted, proceed to die
                exit(1);
            }
        }
    }

    ~Array()
    {
        if (this->on_heap && this->__heap_buf != nullptr) {
            free(this->__heap_buf);
        }
    }

    Array(const Array& other)
    {
        if (this->on_heap) {
            this->__heap_buf = (T*)malloc(sizeof(T) * length);
            if (this->__heap_buf == nullptr) {
                fprintf(stderr, "[CORE] Memory allocation error; panicking\n");
                exit(1);
            }
            memcpy(this->__heap_buf, other.__heap_buf, sizeof(T) * this->length);
        } else {
            memcpy(this->__stack_buf, other.__stack_buf, sizeof(T) * this->length);
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;

        if (this->on_heap) free(this->__heap_buf);

        this->length = other.length;
        this->on_heap = other.on_heap;

        if (this->on_heap) {
            this->__heap_buf = (T*)malloc(sizeof(T) * this->length);
            if (!this->__heap_buf) {
                fprintf(stderr, "[CORE] Memory allocation error; panicking\n");
                exit(1);
            }
            memcpy(this->__heap_buf, other.__heap_buf, sizeof(T) * this->length);
        } else {
            memcpy(this->__stack_buf, other.__stack_buf, sizeof(T) * this->length);
        }

        return *this;
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
            return &this->__heap_buf[idx];
        }
        else {
            return &this->__stack_buf[idx];
        }
    }

    /// returns the internal array
    T* get_buffer()
    {
        if (this->on_heap) return this->__heap_buf;
        else return this->__stack_buf;
    }
};

}


#endif // ST_ARRAY_H
