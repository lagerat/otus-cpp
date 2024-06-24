#pragma once

#include <array>
#include <map>
#include <cassert>

template<typename T, T Default, size_t Depth = 2>
class Matrix
{
public:
    using Key = std::array<size_t, Depth>;
    using Map = std::map<Key, T>;

    auto operator[](size_t i)
    {
        return Value<Matrix, T, Depth>(this, i);
    }

    template<typename ...Args>
    auto operator()(Args... args)
    {
        return Value<Matrix, T, Depth>(this, {size_t(args)...});
    }

    const T& get(const Key& key) const
    {
        auto iter = _map.find(key);
        if (iter == _map.end())
        {
            return _default;
        }
        return iter->second;
    }

    void set(const Key& key, T value)
    {
        auto iter = _map.find(key);
        if (iter == _map.end())
        {
            if (value != Default)
            {
                _map.emplace(key, value);
            }
            return;
        }

        if (value == Default)
        {
            _map.erase(iter);
            return;
        }
        iter->second = value;
    }

    size_t size()
    {
        return _map.size();
    }

    auto begin()
    {
        return _map.begin();
    }

    auto end()
    {
        return _map.end();
    }

    void clear()
    {
        _map.clear();
    }

private:
    Map _map;
    const T _default = Default;

    template<typename Matrix, typename U, size_t Dimension = 2>
    class Value
    {
    public:
        using Key = std::array<size_t, Dimension>;

        Value() = delete;

        explicit Value(Matrix* matrix, Key key) : _matrix(matrix), _key(key), _index(Dimension)
        {
            static_assert(Dimension > 0, "Empty depth");
        }

        explicit Value(Matrix* matrix, size_t i) : _matrix(matrix), _key({i}), _index(1)
        {
            static_assert(Dimension > 0, "Empty depth");
        }

        auto& operator[](size_t i)
        {
            assert(_index < Dimension && "Out of depth");
            _key[_index] = i;
            ++_index;
            return *this;
        }

        const auto& get() const
        {
            assert(_index == Dimension && "Wrong depth");
            return _matrix->get(_key);
        }

        U operator=(U value)
        {
            assert(_index == Dimension && "Wrong depth");
            _matrix->set(_key, value);
            return value;
        }

        bool operator==(const U& value) const
        {
            return get() == value;
        }

    private :
        Matrix* _matrix;
        Key _key;
        size_t _index;
    };
};