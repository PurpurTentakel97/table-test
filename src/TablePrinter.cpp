
#include "TablePrinter.hpp"
#include <iostream>
#include <iomanip>

static constexpr size_t cell_width{ 20 };

void TablePrinter::print(const Table &table) {
    size_t row_count{ 0 };
    size_t column_count{ 0 };
    std::stringstream ss;

    auto const line{ [](size_t const column, std::stringstream &ss) {
        ss << '+';
        for (size_t i = 0; i <= column; ++i) {
            ss << std::string(cell_width, '-') << '+';
        }
        ss << '\n';
    }};

    for (auto const &cell : table.m_cells) {
        if (row_count < cell.m_row) {
            row_count = cell.m_row;
        }
        if (column_count < cell.m_column) {
            column_count = cell.m_column;
        }
    }
    row_count += 1;
    column_count += 1;

    line(column_count, ss);

    for (size_t row = 0; row <= row_count; ++row) {
        if (row == 0) {
            for (size_t column = 0; column <= column_count; ++column) {
                ss << "| " << std::setw(cell_width - 2);
                if (column == 0) {
                    ss << ' ' << ' ';
                } else {
                    ss << std::to_string(column) << ' ';
                }
            }
            ss << "|\n";
        } else {
            for (size_t column = 0; column <= column_count; ++column) {
                ss << "| " << std::setw(cell_width - 2);
                if (column == 0) {
                    ss << std::to_string(row) << ' ';
                } else {
                    ss << table.get_cell(static_cast<int>(row - 1), static_cast<int>(column - 1)).m_str_value << ' ';
                }
            }
            ss << "|\n";
        }
        line(column_count, ss);
    }

    std::cout << ss.str();
}
