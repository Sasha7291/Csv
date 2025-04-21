#pragma once

#ifdef QT
#include <QVector>
#else
#include <vector>
#endif


namespace csv
{
#ifdef QT
template<class T>
using Data = QVector<T>;
#else
template<class T>
using Data = std::vector<T>;
#endif
}
