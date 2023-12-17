
#include "Table.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

static constexpr size_t cell_width{ 18 };

Cell const &Table::get_special_cell(int row, int column) const {
    for (auto &c : m_special_cells) {
        bool const found = (c.m_row == row) && (c.m_column == column);
        if (found) {
            return c;
        }
    }
    throw std::runtime_error{ index_out_of_range_exception_string(row, column) };
}

Cell &Table::get_special_cell(int row, int column) {
    for (auto &c : m_special_cells) {
        bool const found = (c.m_row == row) && (c.m_column == column);
        if (found) {
            return c;
        }
    }
    throw std::runtime_error{ index_out_of_range_exception_string(row, column) };
}

Cell const *Table::get_cell_unsafe(int const row, int const column) const {
    for (auto &c : m_cells) {
        bool const found = (c.m_row == row) && (c.m_column == column);
        if (found) {
            return &c;
        }
    }
    return nullptr;
}

Cell *Table::get_cell_unsafe(int const row, int const column) {
    for (auto &c : m_cells) {
        bool const found = (c.m_row == row) && (c.m_column == column);
        if (found) {
            return &c;
        }
    }
    return nullptr;
}

void Table::update_numbered_table() {
    // first column
    auto constexpr first_column{ 0 };
    for (int row = 0; row <= m_row_count; ++row) {
        if (row == 0) {
            if (m_headline_set) {
                continue;
            } else {
                get_special_cell(row, first_column).set_value("---");
            }
        } else {
            get_special_cell(row, first_column).set_value(row);
        }


    }

    if (m_headline_set) {
        return;
    }

    // row
    auto constexpr fist_row{ 0 };
    for (int column = 1; column <= m_column_count; ++column) {
        get_special_cell(fist_row, column).set_value(column);
    }
}

Table::Table(int const row_count, int const column_count) : m_row_count{ row_count }, m_column_count{ column_count } {
    for (int row = 1; row <= row_count; ++row) {
        for (int column = 1; column <= column_count; ++column) {
            m_cells.emplace_back(row, column);
        }
    }
    for (int column = 0; column <= column_count; ++column) {
        m_special_cells.emplace_back(0, column);
    }

    for (int row = 1; row <= m_row_count; ++row) {
        m_special_cells.emplace_back(row, 0);
    }
    update_numbered_table();
}

int Table::row_count() const {
    return m_row_count;
}

int Table::column_count() const {
    return m_column_count;
}

bool Table::has_cell(int const row, int const column) const {
    return get_cell_unsafe(row, column) != nullptr;
}

Cell &Table::get_cell(int const row, int const column) {
    auto const cell = get_cell_unsafe(row, column);
    if (not cell) {
        throw std::runtime_error(index_out_of_range_exception_string(row, column));
    }
    return *cell;
}

Cell const &Table::get_cell(int const row, int const column) const {
    auto const cell = get_cell_unsafe(row, column);
    if (not cell) {
        throw std::runtime_error(index_out_of_range_exception_string(row, column));
    }
    return *cell;
}

void Table::clear_cell(int const row, int const column) {
    get_cell(row, column).clear();
}

int Table::append_row() {
    auto const old_row_count{ m_row_count++ };
    for (int column = 1; column <= m_column_count; ++column) {
        m_cells.emplace_back(m_row_count, column);
    }
    return m_row_count;
}

bool Table::is_headlines_shown() const {
    return m_headline_set;
}

void Table::show_headlines(bool const show) {
    m_headline_set = show;
}

void Table::set_headline(int const column, std::string const &entry) {
    if (column == 0) {
        throw std::runtime_error{ "special cell 0/0 can not be edited" };
    }
    if (column > m_column_count) {
        throw std::runtime_error{ "column out of range: special cells" };
    }
    get_special_cell(0, column).set_value(entry);
}

void Table::clear_headline(int const column) {
    if (column == 0) {
        throw std::runtime_error{ "special cell 0/0 can not be edited" };
    }
    if (column > m_column_count) {
        throw std::runtime_error{ "column out of range: special cells" };
    }
    get_special_cell(0, column).clear();
}

void Table::set_headlines(std::vector<std::string> const &headlines) {
    if (m_column_count != headlines.size()) {
        throw std::runtime_error{ "missmatch of column count and headline count" };
    }

    auto constexpr first_row{ 0 };
    for (int column = 1; column <= m_column_count; ++column) {
        get_special_cell(first_row, column).set_value(headlines[column - 1]);
    }
}

void Table::clear_headlines() {
    auto constexpr first_row{ 0 };
    for (int column = 1; column <= m_column_count; ++column) {
        get_special_cell(0, column).set_value(std::monostate{ });
    }
    update_numbered_table();
}

void Table::set_numbered_table(bool const counted) {
    m_numbered_table = counted;
    update_numbered_table();
}

bool Table::is_table_numbered() const {
    return m_numbered_table;
}

void Table::set_cell_callback(int const row, int const column, std::function<void(Cell &)> const &callback) {
    auto &cell = get_cell(row, column);
    cell.set_callback(callback);
}

void Table::test_cell_callback(int const row, int const column) {
    get_cell(row, column).test_callback();
}

void Table::print() {
    std::stringstream ss;
    auto constexpr first_row{ 0 };
    auto constexpr first_column{ 0 };

    auto const line{ [this](size_t column, std::stringstream &ss) {
        if (m_numbered_table) {
            ++column;
        }
        ss << '+';
        for (int i = 1; i <= column; ++i) {
            ss << std::string(cell_width, '-') << '+';
        }
        ss << '\n';
    }};

    auto const print_special_cell{ [this](int const row, int const column, std::stringstream &ss) {
        ss << "| "
           << std::setw(cell_width - 2)
           << get_special_cell(row, column).m_str_value
           << ' ';
    }};

    auto const print_row{ [this](int const row, std::stringstream &ss) {
        for (int column = 1; column <= m_column_count; ++column) {
            ss << "| "
               << std::setw(cell_width - 2)
               << get_cell(row, column).m_str_value
               << ' ';
        }
    }};

    line(m_column_count, ss);

    if (m_numbered_table) {
        for (int column = 0; column <= m_column_count; ++column) {
            print_special_cell(first_row, column, ss);
        }
        ss << "|\n";
        line(m_column_count, ss);
    } else if (m_headline_set) {
        for (int column = 1; column <= m_column_count; ++column) {
            print_special_cell(first_row, column, ss);
        }
        ss << "|\n";
        line(m_column_count, ss);
    }

    for (int row = 1; row <= m_row_count; ++row) {
        if (m_numbered_table) {
            print_special_cell(row, first_column, ss);
        }
        print_row(row, ss);
        ss << "|\n";
        line(m_column_count, ss);
    }

    std::cout << ss.str();
}


