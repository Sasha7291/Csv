#pragma once

#include <sstream>
#include <vector>

namespace csv
{

template<class T>
class Row
{
    template<class K>
    friend std::istream &operator>>(std::istream &in, Row<K> &row);
    template<class K>
    friend std::ostream &operator<<(std::ostream &out, const Row<K> &row);

public:
    Row(const std::vector<T> &data) noexcept;
    Row(std::vector<T> &&data) noexcept;
    Row() noexcept = default;
    ~Row() noexcept = default;

    Row(const Row &other) noexcept = default;
    Row(Row &&other) noexcept = default;
    Row &operator=(const Row &other) noexcept = default;
    Row &operator=(Row &&other) noexcept = default;

    [[nodiscard]] T operator[](const std::size_t index) const;
    [[nodiscard]] std::size_t size() const;

private:
    std::vector<T> data_;

};

template<class T>
Row<T>::Row(const std::vector<T> &data) noexcept
    : data_(data)
{}

template<class T>
Row<T>::Row(std::vector<T> &&data) noexcept
    : data_(std::move(data))
{}

template<class T>
T Row<T>::operator[](const std::size_t index) const
{
    return data_[index];
}

template<class T>
std::size_t Row<T>::size() const
{
    return data_.size();
}

template<class T>
std::istream &operator>>(std::istream &in, Row<T> &row)
{
    row.data_.clear();
    std::string line;
    std::getline(in, line);
    std::stringstream lineStream(line);

    std::string word;
    while (std::getline(lineStream, word, ','))
    {
        std::stringstream wordStream(word);
        T temp;
        wordStream >> temp;
        row.data_.push_back(temp);
    }

    return in;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const Row<T> &row)
{
    auto itb = row.data_.cbegin();
    auto ite = row.data_.cend();
    for (auto it = itb; it != ite; ++it)
    {
        out << *it;

        if (std::distance(itb, it) == row.data_.size() - 1)
            out << "\n";
        else
            out << ",";
    }

    return out << std::endl;
}

}
