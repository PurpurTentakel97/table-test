#pragma once

#include "Cell.hpp"
#include <vector>

class Table final {
private:
    std::vector<Cell> m_cells;

public:
    Table(int row_count, int column_count) {
        for (int i = 0; i < row_count; ++i) {
            for (int j = 0; j < column_count; ++j) {
                m_cells.emplace_back(i, j);
            }
        }
    }

    [[nodiscard]] Cell &get_cell(int x, int y) {
        for (auto &c: m_cells) {
            bool const found = (c.x == x) && (c.y == y);
            if (found) {
                return c;
            }
        }
        throw std::runtime_error("no such cell");
    }

    Cell &set_cell(int x, int y) {
        for (auto &c: m_cells) {
            bool const found = (c.x == x) && (c.y == y);
            if (found) {
                return c;
            }
        }
        auto &c = m_cells.emplace_back(x, y);
        return c;
    }
};