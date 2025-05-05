#pragma once

#include "csv_exception.hpp"
#include "csv_row.hpp"

#include <fstream>


namespace csv
{

template<class T>
class Writer
{

public:
    Writer(Direction dir) noexcept;
    ~Writer() noexcept = default;

    Writer(const Writer &) = delete;
    Writer(Writer &&) = delete;
    Writer &operator=(const Writer &) = delete;
    Writer &operator=(Writer &&) = delete;

    void operator()(const std::string &fileName, const Data<Data<T>> &data) const;

private:
    void writeColumns(std::ofstream &file, const Data<Data<T>> &data);
    void writeRows(std::ofstream &file, const Data<Data<T>> &data);

    Direction dir_;

};

template<class T>
Writer<T>::Writer(Direction dir) noexcept
    : dir_(dir)
{}

template<class T>
void Writer<T>::operator()(const std::string &fileName, const Data<Data<T>> &data) const
{
	if (fileName.empty())
        throw Exception{"File name is null"};
	
	if (!fileName.ends_with(".csv"))
        throw Exception{"Invalid file format"};
	
    std::ofstream file{fileName};
    if (!file.is_open())
        throw Exception{"File " + fileName + " is not opened"};


}

template<class T>
void Writer<T>::writeColumns(std::ofstream &file, const Data<Data<T>> &data)
{
    Data<T> row(data.size());
    for (int i = 0; i < data[0].size(); ++i)
    {
        for (int j = 0; j < data.size(); ++j)
            row[j] = data[j][i];

        file << Row{row};
    }
}

template<class T>
void Writer<T>::writeRows(std::ofstream &file, const Data<Data<T> > &data)
{
    for (const auto &line : data)
        file << Row{line};
}

}
