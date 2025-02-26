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
        if (__refs) {
            __refs->val--;
            if (__refs->val == 0) {
                delete __val;
                delete __refs;
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

/// makes a brand new reference. the class used must have a constructor with no parameters
template<typename T>
Ref<T> newref()
{
    return Ref<T>(new T());
}

/// makes a reference from another reference.
template<typename T>
Ref<T> newref(const Ref<T>& ref)
{
    return Ref<T>(ref);
}

}

#endif // ST_REF_H
