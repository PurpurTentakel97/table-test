
#include "TablePrinter.hpp"
#include <iostream>
#include <iomanip>

static constexpr size_t cell_width{15};

void TablePrinter::print(const Table &table) {
    size_t row_count{0};
    size_t column_count{0};
    std::stringstream ss;

    auto const line{[](size_t const column, std::stringstream &ss) {
        ss << '+';
        for (size_t i = 0; i <= column; ++i) {
            ss << std::string(cell_width, '-') << '+';
        }
        ss << '\n';
    }};

    for (auto const &cell: table.m_cells) {
        if (row_count < cell.x) {
            row_count = cell.x;
        }
        if (column_count < cell.y) {
            column_count = cell.y;
        }
    }
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
                    ss << table.get_cell(column-1, row-1).str_value << ' ';
                }
            }
            ss << "|\n";
        }
        line(column_count, ss);
    }

    std::cout << ss.str();
}
