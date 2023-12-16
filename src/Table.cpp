
#include "Table.hpp"

Table::Table(int row_count, int column_count) {
    for (int i = 0; i < row_count; ++i) {
        for (int j = 0; j < column_count; ++j) {
            m_cells.emplace_back(i, j);
        }
    }
}

Cell &Table::get_cell(int x, int y) {
    for (auto &c: m_cells) {
        bool const found = (c.x == x) && (c.y == y);
        if (found) {
            return c;
        }
    }
    throw std::runtime_error("no such cell");
}

Cell const &Table::get_cell(int x, int y) const {
    for (auto &c: m_cells) {
        bool const found = (c.x == x) && (c.y == y);
        if (found) {
            return c;
        }
    }
    throw std::runtime_error("no such cell");
}

Cell &Table::set_cell(int x, int y) {
    for (auto &c: m_cells) {
        bool const found = (c.x == x) && (c.y == y);
        if (found) {
            return c;
        }
    }
    auto &c = m_cells.emplace_back(x, y);
    return c;
}
