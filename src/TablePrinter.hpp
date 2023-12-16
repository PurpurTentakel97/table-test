#pragma once

#include "Table.hpp"
#include <iostream>
#include <iomanip>

class TablePrinter final {
public:
    void print(Table const &table) const;
};
