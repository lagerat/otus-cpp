#ifndef HELLOWORLD_CLI_ALLOCATOR_H
#define HELLOWORLD_CLI_ALLOCATOR_H


#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>

template<typename T>
struct allocator {
    using value_type = T;

    struct rebind {
        using other = allocator<T>;
    };

    void *allocate_additionalMemory() {
        auto dedicatedMem = std::malloc(10 * sizeof(T));
        if (!dedicatedMem) {
            throw std::bad_alloc();
        }
        allocatedMemoryCount += 10;
        auto saveMem = reinterpret_cast<bool *>(std::realloc(usedMem, allocatedMemoryCount));
        if (saveMem == nullptr) {
            throw std::bad_alloc();
        }
        usedMem = saveMem;
        for (int i = allocatedMemoryCount - 10; i < allocatedMemoryCount; ++i) {
            usedMem[i] = false;
        }
        memoryVector.push_back(dedicatedMem);
        return dedicatedMem;
    }


    allocator() {
        allocate_additionalMemory();
    }

    ~allocator() {
        for (auto mem: memoryVector) {
            free(mem);
        }
    };

    T *allocate([[maybe_unused]]  std::size_t n) {
        if (n > 1) {
            throw std::bad_alloc(); //If this allocator using for vector
        }
        for (int i = 0; i < allocatedMemoryCount; ++i) {
            if (!usedMem[i]) {
                usedMem[i] = true;
                auto p = reinterpret_cast<T *>(memoryVector[i / 10]);
                return (p + (i % 10));
            }
        }
        auto p = reinterpret_cast<T *>(allocate_additionalMemory());
        usedMem[(memoryVector.size() - 1) * 10] = true;
        return p;
    }

    void deallocate([[maybe_unused]] T *p, [[maybe_unused]] std::size_t n) {
        bool elementFind = false;
        for (auto dedicatedMem: memoryVector) {
            auto find = reinterpret_cast<T *>(dedicatedMem);
            for (int i = 0; i < 10; ++i) {
                if ((find + i) == p) {
                    usedMem[i] = false;
                    elementFind = true;
                    break;
                }
            }
            if (elementFind) {
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

private:
    std::vector<void *> memoryVector;
    bool *usedMem = nullptr;
    int allocatedMemoryCount = 0;
};

#endif //HELLOWORLD_CLI_ALLOCATOR_H
