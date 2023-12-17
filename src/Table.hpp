#pragma once

#include "Cell.hpp"
#include <vector>

class Table final {
private:
    std::vector<Cell> m_cells;

    friend class TablePrinter;

    [[nodiscard]] Cell const *get_cell_unsafe(int row, int column) const;

    [[nodiscard]] Cell *get_cell_unsafe(int row, int column);

public:
    Table(int row_count, int column_count);

    [[nodiscard]] bool has_cell(int row, int column) const;

    [[nodiscard]] Cell &get_cell(int row, int column);

    [[nodiscard]] Cell const &get_cell(int row, int column) const;

    Cell &set_cell(int row, int column);

    Cell &set_value(int row, int column, auto value) {
        auto cell = get_cell_unsafe(row, column);
        if (not cell) {
            auto &new_cell = set_cell(row, column);
            new_cell.set_value(value);
            return new_cell;
        }
        cell->set_value(value);
        return *cell;
    }

    void clear_cell(int row, int column);

    void set_cell_callback(int row, int column, std::function<void(Cell &)> const &callback);

    void test_cell_callback(int row, int column);
};