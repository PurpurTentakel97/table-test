#pragma once

#include "Cell.hpp"
#include <vector>

class Table final {
private:
    std::vector<Cell> m_cells;

    friend class TablePrinter;

public:
    Table(int row_count, int column_count);

    [[nodiscard]] Cell &get_cell(int x, int y);

    [[nodiscard]] Cell const &get_cell(int x, int y) const;

    Cell &set_cell(int x, int y);
};