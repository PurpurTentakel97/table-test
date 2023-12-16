#pragma once

#include "Cell.hpp"
#include <vector>

class Table final {
private:
    std::vector<Cell> m_cells;

    friend class TablePrinter;

public:
    Table(int row_count, int column_count);

    [[nodiscard]] Cell &get_cell(int row, int column);

    [[nodiscard]] Cell const &get_cell(int row, int column) const;

    Cell &set_cell(int row, int column);

    Cell &set_value(int row, int column, auto value) {
        auto &cell = get_cell(row, column);
        cell.set_value(value);
        return cell;
    }

    void clear_cell(int row, int column);

    void set_cell_callback(int row, int column, std::function<void(Cell &)> const &callback);

    void test_cell_callback(int row, int column);
};