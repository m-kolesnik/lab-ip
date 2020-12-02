#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
// 5

namespace TYP {

template <class T>
class Vector {
public:
    using iterator = T*;

    Vector();
    explicit Vector(size_t size);
    Vector(size_t size, const T& value);
    Vector(iterator first, iterator last);
    Vector(const std::initializer_list<T>& lst);
    Vector(const Vector<T>& other);
    ~Vector();

    Vector<T>& operator=(const Vector<T>& other);
    bool operator==(const Vector<T>& other) const;
    bool operator!=(const Vector<T>& other) const;
    bool operator<(const Vector<T>& other) const;
    bool operator>(const Vector<T>& other) const;
    bool operator<=(const Vector<T>& other) const;
    bool operator>=(const Vector<T>& other) const;

    
    iterator begin() const;
    iterator end() const;


    size_t size() const;
    size_t capacity() const;
    bool isEmpty() const;
    void resize(size_t size, const T& value = T());
    void reserve(size_t size);

    
    T& operator[](size_t index) const;
    T& at(size_t index) const;
    T* data() const;

    
    void push_back(const T& value);
    void pop_back();

    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    void clear();

private:
    size_t m_size{0};
    size_t m_capacity{0};
    T* m_buffer{nullptr};
};

}

namespace TYP {

template<class T>
Vector<T>::Vector()
    : Vector(0)
{}

template<class T>
Vector<T>::Vector(size_t size)
    : m_size(size), m_capacity(size)
{
    m_buffer = new T[size];
    for (size_t i = 0; i < size; ++i)
        m_buffer[i] = T();
}

template<class T>
Vector<T>::Vector(size_t size, const T& value)
    : Vector(size)
{
    for (size_t i = 0; i < m_size; ++i)
        m_buffer[i] = value;
};

template<class T>
Vector<T>::Vector(iterator first, iterator last)
    : Vector(std::distance(first, last))
{
    std::copy(first, last, m_buffer);
}

template<class T>
Vector<T>::Vector(const std::initializer_list<T>& lst)
    : Vector(lst.size())
{
    for(size_t i = 0; i < m_size; ++i)
        *(m_buffer + i) = *(lst.begin() + i);
}

template<class T>
Vector<T>::Vector(const Vector<T>& other)
    : Vector(std::distance(other.begin(), other.end()))
{
    std::copy(other.begin(), other.end(), m_buffer);
}

template<class T>
Vector<T>::~Vector()
{
    delete[] m_buffer;
    // std::cout << "destruct!\n";
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other) {
        delete[] m_buffer;
        m_buffer = new T[other.size()];
        std::copy(other.begin(), other.end(), m_buffer);
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }
    return *this;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& other) const
{
    return std::equal(begin(), end(), other.begin());
}

template<class T>
bool Vector<T>::operator!=(const Vector<T>& other) const {
    return !std::equal(begin(), end(), other.begin());
}
template<class T>
bool Vector<T>::operator<(const Vector<T>& other) const
{
    return std::lexicographical_compare(begin(), end(),
            other.begin(), other.end());
}
template<class T>
bool Vector<T>::operator>(const Vector<T>& other) const {
    return std::lexicographical_compare(begin(), end(),
            other.begin(), other.end(),
            [](const T& a, const T& b) {return a > b;});
}
template<class T>
bool Vector<T>::operator<=(const Vector<T>& other) const {
    return std::lexicographical_compare(begin(), end(),
            other.begin(), other.end(),
            [](const T& a, const T& b) {return a <= b;});
}
template<class T>
bool Vector<T>::operator>=(const Vector<T> &other) const {
    return std::lexicographical_compare(begin(), end(),
            other.begin(), other.end(),
            [](const T& a, const T& b) {return a >= b;});
}

template<class T>
typename Vector<T>::iterator Vector<T>::begin() const {
    return m_buffer;
};
template<class T>
typename Vector<T>::iterator Vector<T>::end() const {
    return &*(m_buffer + m_size);
};


template<class T>
size_t Vector<T>::size() const {
    return m_size;
};
template<class T>
size_t Vector<T>::capacity() const {
    return m_capacity;
};
template<class T>
bool Vector<T>::isEmpty() const {
    return m_size == 0;
};

template<class T>
void Vector<T>::resize(size_t size, const T& value)
{
    T* new_obj = new T[size];
    // size_t i = 0;
    if (size >= m_capacity) {
        // for (; i < m_size; ++i) new_obj[i] = m_buffer[i];
        std::move(begin(), end(), new_obj);
        for (size_t i = m_size; i < size; ++i) new_obj[i] = value;
    } else {
        for (size_t i = 0; i < size; ++i) new_obj[i] = m_buffer[i];
    }
    delete[] m_buffer;
    m_buffer = new_obj;
    m_capacity = size;
    m_size = size;
}
template<class T>
void Vector<T>::reserve(size_t size)
{
    if (size > m_capacity) {
        T* new_obj = new T[size];
        m_capacity = size;
        // size_t i = 0;
        // for (; i < m_size; ++i) new_obj[i] = m_buffer[i];
        std::move(begin(), end(), new_obj);
        for (size_t i = m_size; i < size; ++i) new_obj[i] = T();
        delete[] m_buffer;
        m_buffer = new_obj;
    }
}

// element access
template<class T>
T& Vector<T>::operator[](size_t index) const {
    return m_buffer[index];
}
template<class T>
T& Vector<T>::at(size_t index) const {
    if (index >= m_size)
        throw std::out_of_range("Vector: out of range");
    return m_buffer[index];
}
template<class T>
T* Vector<T>::data() const {
    return m_buffer;
}

template<class T>
void Vector<T>::push_back(const T& value) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    *end() = value;
    m_size++;
}

template<class T>
void Vector<T>::pop_back() {
    m_size--;
}

template<class T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T& value) {
    iterator iter;
    size_t distance = std::distance(begin(), pos);

    if (distance == m_size) {
        push_back(value);
        iter = end() - 1;
    } else {
        if (m_size == m_capacity) {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        for (size_t i = m_size; i > distance; --i)
            m_buffer[i] = m_buffer[i - 1];
        m_buffer[distance] = value;
        m_size++;
        iter = pos;
    }
    return iter;
}

template<class T>
typename Vector<T>::iterator Vector<T>::erase(iterator pos) {
    auto res = end();
    if (pos != end()) {
        res = pos;
        for (auto it = pos; it != end() - 1; ++it) {
            *it = *(it + 1);
        }
    }
    m_size--;
    return res;
}

template<class T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last) {
    size_t distance = std::distance(first, last);
    if (distance == m_size) {
        // delete[] m_buffer;
        m_size = 0;
        return nullptr;
    } else {
        auto it = first;
        for (; it != last; ++it)
            *it = *(it + distance);
        m_size -= distance;
        return it;
    }
}

template<class T>
void Vector<T>::clear() {
    erase(begin(), end());
};

}