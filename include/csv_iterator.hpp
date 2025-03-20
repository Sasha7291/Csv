#pragma once

#include "csv_row.hpp"

#include <iterator>

namespace csv
{

template<class T>
class Iterator : public std::iterator<std::input_iterator_tag, Row<T>>
{

public:
    Iterator(std::istream& in);
    Iterator();
    ~Iterator() = default;

    Iterator &operator++();
    Iterator operator++(int);
    [[nodiscard]] const Row<T> &operator*() const;
    [[nodiscard]] const Row<T> *operator->() const;
    [[nodiscard]] bool operator==(const Iterator &other);
    [[nodiscard]] bool operator!=(const Iterator &other);

private:
    std::istream* istream_;
    Row<T> row_;

};

template<class T>
Iterator<T>::Iterator(std::istream &in)
    : istream_(in.good() ? &in : nullptr)
{
    ++(*this);
}

template<class T>
Iterator<T>::Iterator()
    : istream_(nullptr)
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
    Iterator temp(*this);
    ++(*this);
    return temp;
}

template<class T>
const Row<T> &Iterator<T>::operator*() const
{
    return row_;
}

template<class T>
const Row<T> *Iterator<T>::operator ->() const
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
