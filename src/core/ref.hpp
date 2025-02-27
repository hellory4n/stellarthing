#ifndef ST_REF_H
#define ST_REF_H
#include "core/core.hpp"

namespace starry {

/// reference counter
template <typename T>
class Ref {
private:
    // man
    struct Numptr {
        nint val = 1;
    };
    
    T* __val = nullptr;
    Numptr* __refs = nullptr;

    void __cleanup()
    {
        if (this->__refs != nullptr) {
            this->__refs->val--;
            if (this->__refs->val == 0) {
                delete this->__val;
                delete this->__refs;
            }
        }
    }

public:
    Ref(T* ptr)
    {
        if (ptr != nullptr) {
            this->__refs = new Numptr();
        }
        this->__val = ptr;
    }

    Ref(const Ref& obj)
    {
        __val = obj.__val;
        __refs = obj.__refs;
        if (__refs != nullptr) {
            __refs->val++;
        }
    }

    Ref& operator =(const Ref& obj)
    {	
        if (this == &obj) {
            return *this;
        }

        this->__cleanup();

        this->__val = obj.__val;
        this->__refs = obj.__refs;
        if (this->__refs != nullptr) {
            this->__refs->val++;
        }

        return *this;
    }

    /// returns how many references the object has
    nint get_ref_count()
    {
        return this->__refs != nullptr ? this->__refs->val : 0;
    }

    T* get()
    {
        return this->__val;
    }

    T* operator ->()
    {
        return this->__val;
    }

    T* operator *()
    {
        return this->__val;
    }

    ~Ref()
    {
        this->__cleanup();
    }
};

}

#endif // ST_REF_H
