#pragma once

#include "csv_exception.hpp"
#include "csv_range.hpp"

#include <filesystem>
#include <fstream>


namespace csv
{

template<class T>
class Reader
{

public:
    Reader(Direction dir = Rows) noexcept;
    ~Reader() noexcept = default;

    Reader(const Reader &) = delete;
    Reader(Reader &&) = delete;
    Reader &operator=(const Reader &) = delete;
    Reader &operator=(Reader &&) = delete;

    [[nodiscard]] Data<Data<T>> operator()(const std::filesystem::path &path) const;

private:
    [[nodiscard]] Data<Data<T>> readColumns(std::ifstream &file) const;
    [[nodiscard]] Data<Data<T>> readRows(std::ifstream &file) const;

    Direction dir_;

};

template<class T>
Reader<T>::Reader(Direction dir) noexcept
    : dir_{dir}
{}

template<class T>
Data<Data<T>> Reader<T>::operator()(const std::filesystem::path &path) const
{
    if (path.empty())
        throw Exception{"File name is null"};

    if (!path.string().ends_with(".csv"))
        throw Exception{"Invalid file format"};

    std::ifstream file{path};
    if (!file.is_open())
        throw Exception{"File " + path.string() + " is not opened"};

    return (dir_ == Rows) ? readRows(file) : readColumns(file);
}

template<class T>
Data<Data<T>> Reader<T>::readColumns(std::ifstream &file) const
{
    Data<Data<T>> result;
    for (auto &row : InputRange<T>{file})
    {
        if (result.size() < row.size())
            for (int i = 0; i < row.size(); ++i)
                result.push_back(Data<T>{});

        for (int i = 0; i < row.size(); ++i)
            result[i].push_back(row[i]);
    }

    file.close();
    return result;
}

template<class T>
Data<Data<T>> Reader<T>::readRows(std::ifstream &file) const
{
    Data<Data<T>> result;
    for (auto &row : InputRange<T>{file})
    {
        Data<T> vectorRow;
        vectorRow.reserve(row.size());

        for (auto i = 0ull; i < row.size(); ++i)
            vectorRow.push_back(row[i]);

        result.push_back(vectorRow);
    }

    file.close();
    return result;
}

}
