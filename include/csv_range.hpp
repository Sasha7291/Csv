#pragma once

#include "iterator.hpp"


namespace csv
{

template<class T>
class InputRange
{

public:
    InputRange(std::istream &in);

    Iterator<T> begin();
    Iterator<T> end();

private:
    std::istream &stream_;

};

template<class T>
InputRange<T>::InputRange(std::istream &in)
    : stream_(in)
{}

template<class T>
Iterator<T> InputRange<T>::begin()
{
    return Iterator<T>(stream_);
}

template<class T>
Iterator<T> InputRange<T>::end()
{
    return Iterator<T>();
}

}
