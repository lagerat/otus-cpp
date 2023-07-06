#ifndef HELLOWORLD_CLI_LIMITED_ALLOCATOR_H
#define HELLOWORLD_CLI_LIMITED_ALLOCATOR_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

template<typename T>
struct limited_allocator {
    using value_type = T;

    struct rebind {
        using other = limited_allocator<T>;
    };

    limited_allocator() {
        dedicatedMem = std::malloc(10 * sizeof(T));
        if (!dedicatedMem) {
            throw std::bad_alloc();
        }
    }

    ~limited_allocator() {
        free(dedicatedMem);
    };

    T *allocate([[maybe_unused]]  std::size_t n) {
        if (n > 1) {
            throw std::bad_alloc(); //If this allocator using for vector
        }
        for (int i = 0; i < 10; ++i) {
            if (!usedMem[i]) {
                usedMem[i] = true;
                auto p = reinterpret_cast<T *>(dedicatedMem);
                return (p + i);
            }
        }
        throw std::bad_alloc(); // If memory full
    }

    void deallocate([[maybe_unused]] T *p, [[maybe_unused]] std::size_t n) {
        auto find = reinterpret_cast<T *>(dedicatedMem);
        bool elementFind = false;
        for (int i = 0; i < 10; ++i) {
            if ((find + i) == p) {
                usedMem[i] = false;
                elementFind = true;
                break;
            }
        }
        if (!elementFind) {
            throw std::bad_alloc();
        }
    }

    template<typename U, typename ... Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U *p) {
        p->~U();
    }

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

    bool usedMem[10]{};
    void *dedicatedMem = nullptr;
};

template <class T, class U>
constexpr bool operator== (const limited_allocator<T> &a1, const limited_allocator<U> &a2) noexcept {
    return a1.memoryVector == a2.memoryVector;
}

#endif //HELLOWORLD_CLI_LIMITED_ALLOCATOR_H
