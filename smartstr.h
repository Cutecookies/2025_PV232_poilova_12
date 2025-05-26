#ifndef SMARTSTR_H
#define SMARTSTR_H

#include <QFile>
#include <type_traits>

template <typename T>
class smartPtr {
    T* ptr;

    // Вспомогательная функция для освобождения ресурса
    void reset() {
        if constexpr (std::is_same_v<T, QFile>) {
            if (ptr && ptr->isOpen()) {
                ptr->close();
            }
        }
        delete ptr;
        ptr = nullptr;
    }

public:
    explicit smartPtr(T* obj = nullptr) : ptr(obj) {}

    smartPtr(const smartPtr&) = delete;
    smartPtr& operator=(const smartPtr&) = delete;

    smartPtr(smartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    smartPtr &operator =(smartPtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    ~smartPtr() {
        reset();
    }

    T* operator->() const {
        return ptr;
    }
    T& operator*() const {
        return *ptr;
    }
    T* get() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

#endif // SMARTSTR_H
