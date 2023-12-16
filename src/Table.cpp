
#include "Table.hpp"

Table::Table(int row_count, int column_count) {
    for (int row = 0; row < row_count; ++row) {
        for (int column = 0; column < column_count; ++column) {
            m_cells.emplace_back(row, column);
        }
    }
}

Cell &Table::get_cell(int row, int column) {
    for (auto &c : m_cells) {
        bool const found = (c.m_row == row) && (c.m_column == column);
        if (found) {
            return c;
        }
    }
    throw std::runtime_error("no such cell");
}

Cell const &Table::get_cell(int row, int column) const {
    for (auto &c : m_cells) {
        bool const found = (c.m_row == row) && (c.m_column == column);
        if (found) {
            return c;
        }
    }
    throw std::runtime_error("no such cell");
}

Cell &Table::set_cell(int row, int column) {
    for (auto &c : m_cells) {
        bool const found = (c.m_row == row) && (c.m_column == column);
        if (found) {
            return c;
        }
    }
    auto &c = m_cells.emplace_back(row, column);
    return c;
}

void Table::clear_cell(int row, int column) {
    get_cell(row, column).clear();
}

void Table::set_cell_callback(int row, int column, std::function<void(Cell &)> const &callback) {
    auto &cell = get_cell(row, column);
    cell.set_callback(callback);
}

void Table::test_cell_callback(int row, int column) {
    get_cell(row, column).test_callback();
}


