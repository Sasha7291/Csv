#include "reader.hpp"
#include "writer.hpp"

#include <iostream>

int main()
{
    csv::Reader<double> reader;
    auto data = reader("data.csv");

    for (const auto &row : data)
        std::cout << row[0] << std::endl;

    csv::Writer writer;
    writer("data1.csv", data);

    return 0;
}
