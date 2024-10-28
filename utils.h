#ifndef UTILS_H
#define UTILS_H

#pragma once
#include <iostream>
#include <limits>


template <typename T>
T InputNum(T start, T end)
{
    T param;
    (std::cin >> param);
    while (std::cin.fail() || (std::cin.peek() != '\n') || (param < start) || (param > end))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод, повторите снова\n";
        (std::cin >> param);
    }

    return param;
}

#endif // UTILS_H
