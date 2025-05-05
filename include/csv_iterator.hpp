#pragma once

#include "csv_row.hpp"

#include <iterator>


namespace csv
{

template<class T>
class Iterator
{

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Row<T>;
    using element_type = Row<T>;
    using pointer = value_type *;
    using reference = const value_type &;
    using difference_type = std::ptrdiff_t;

    Iterator(std::istream& in);
    Iterator();
    ~Iterator() = default;

    Iterator &operator++();
    Iterator operator++(int);
    [[nodiscard]] reference operator*() const;
    [[nodiscard]] const pointer operator->() const;
    [[nodiscard]] bool operator==(const Iterator &other);
    [[nodiscard]] bool operator!=(const Iterator &other);

private:
    std::istream *istream_;
    Row<T> row_;

};

template<class T>
Iterator<T>::Iterator(std::istream &in)
    : istream_{in.good() ? &in : nullptr}
{
    ++(*this);
}

template<class T>
Iterator<T>::Iterator()
    : istream_{nullptr}
{}

template<class T>
Iterator<T> &Iterator<T>::operator++()
{
    if (istream_ != nullptr)
        if (!(*istream_ >> row_))
            istream_ = nullptr;

    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator temp{*this};
    ++(*this);
    return temp;
}

template<class T>
Iterator<T>::reference Iterator<T>::operator *() const
{
    return row_;
}

template<class T>
const Iterator<T>::pointer Iterator<T>::operator->() const
{
    return &row_;
}

template<class T>
bool Iterator<T>::operator==(const Iterator &other)
{
    return ((this == &other) || (this->istream_ == nullptr) && (other.istream_ == nullptr));
}

template<class T>
bool Iterator<T>::operator!=(const Iterator &other)
{
    return !((*this) == other);
}

}
