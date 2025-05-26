#ifndef SMARTSTR_H
#define SMARTSTR_H

template <typename T>
class smart_ptr {
    T * ptr;
public:
    smart_ptr(T *obj) : ptr(obj){ }
    ~smart_ptr() {
        delete ptr;
    }

    T* operator->() {
        return ptr;
    }

    T& operator* () {
        return *ptr;
    }
};

#endif // SMARTSTR_H
