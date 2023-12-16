#pragma once

#include "Table.hpp"
#include <iostream>
#include <iomanip>

class TablePrinter final {
public:
    static void print(Table const &table);
};
