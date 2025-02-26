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
		nint val;
	};
	
	T* __val = nullptr;
	Numptr* __refs = nullptr;

    void __cleanup()
	{
		this->__refs->val--;
		if (this->__refs->val <= 0) {
			if (this->__val != nullptr) {
				delete this->__val;
            }
			delete this->__refs;
		}
	}

public:
	Ref(T* ptr)
    {
        this->__val = ptr;
		this->__refs = new Numptr();
		this->__refs->val = 0;
	}

	Ref(const Ref& obj)
	{
		this->__val = obj.__val;
		this->__refs = obj.__refs;
		if (obj.__val != nullptr) {
			this->__refs->val++;
		}
	}

	Ref& operator =(const Ref& obj)
	{
		this->__cleanup();
		
		this->__val = obj.__val;
		this->__refs = obj.__refs;
		if (obj.__val != nullptr) {
			this->__refs->val++;
		}
		return *this;
	}

    /// returns how many references the object has
    nint get_ref_count()
    {
		return this->__refs->val;
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
	    __cleanup();
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
