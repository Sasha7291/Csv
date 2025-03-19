#pragma once

#include "exception.hpp"
#include "range.hpp"

#include <fstream>


namespace csv
{

template<class T>
class Reader
{

public:
    Reader() noexcept = default;
    ~Reader() noexcept = default;

    Reader(const Reader &) = delete;
    Reader(Reader &&) = delete;
    Reader &operator=(const Reader &) = delete;
    Reader &operator=(Reader &&) = delete;

    [[nodiscard]] std::vector<std::vector<T>> operator()(const std::string &fileName) const;

};

template<class T>
std::vector<std::vector<T>> Reader<T>::operator()(const std::string &fileName) const
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw Exception("File " + fileName + " is not opened");

    std::vector<std::vector<T>> result;
    for (auto &row : InputRange<T>(file))
    {
        std::vector<T> vectorRow;
        vectorRow.reserve(row.size());

        for (auto i = 0ull; i < row.size(); ++i)
            vectorRow.push_back(row[i]);

        result.push_back(vectorRow);
    }

    return result;
}

}
