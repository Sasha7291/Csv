#pragma once

#include "exception.hpp"

#include <fstream>


namespace csv
{

class Writer
{

public:
    Writer() noexcept = default;
    ~Writer() noexcept = default;

    Writer(const Writer &) = delete;
    Writer(Writer &&) = delete;
    Writer &operator=(const Writer &) = delete;
    Writer &operator=(Writer &&) = delete;

    template<class T>
    void operator()(const std::string &fileName, const std::vector<std::vector<T>> &data) const;

};

template<class T>
void Writer::operator()(const std::string &fileName, const std::vector<std::vector<T>> &data) const
{
    std::ofstream file(fileName);
    if (!file.is_open())
        throw Exception("File " + fileName + " is not opened");

    for (const auto &line : data)
        file << Row(line);
}

}
