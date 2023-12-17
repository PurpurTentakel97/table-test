#pragma once

#include "Cell.hpp"
#include <list>

static inline const std::function<std::string(int, int)> index_out_of_range_exception_string{
        [](int const row, int const column) -> std::string {
            return "no such cell - row: " + std::to_string(row) + " | column: " + std::to_string(column);
        }};

class Table final {
    friend class TablePrinter;

private:
    std::list<Cell> m_cells;
    std::list<Cell> m_special_cells;
    int m_row_count, m_column_count;
    bool m_headline_set{ false };
    bool m_numbered_table{ false };

    [[nodiscard]] Cell const &get_special_cell(int row, int column) const;

    [[nodiscard]] Cell &get_special_cell(int row, int column);

    [[nodiscard]] Cell const *get_cell_unsafe(int row, int column) const;

    [[nodiscard]] Cell *get_cell_unsafe(int row, int column);

    void update_numbered_table();

public:
    Table(int row_count, int column_count);

    [[nodiscard]] int row_count() const;

    [[nodiscard]] int column_count() const;

    // cells
    [[nodiscard]] bool has_cell(int row, int column) const;

    [[nodiscard]] Cell &get_cell(int row, int column);

    [[nodiscard]] Cell const &get_cell(int row, int column) const;

    // row & column
    int insert_row(int row);

    int append_row();

    void remove_row(int row);

    void pop_row();

    int insert_column(int column);

    int append_column();

    void remove_column(int column);

    void pop_column();

    // values
    Cell &set_value(int row, int column, auto value) {
        auto cell = get_cell_unsafe(row, column);
        if (not cell) {
            throw std::runtime_error{ index_out_of_range_exception_string(row, column) };
        }
        cell->set_value(value);
        return *cell;
    }

    // extra values
    [[nodiscard]] bool is_headlines_shown() const;

    void show_headlines(bool show);

    void set_headline(int column, std::string const &entry);

    void clear_headline(int column);

    void set_headlines(const std::vector<std::string> &headlines);

    void clear_headlines();

    void set_numbered_table(bool counted);

    [[nodiscard]] bool is_table_numbered() const;

    void clear_cell(int row, int column);

    // callbacks
    void set_cell_callback(int row, int column, std::function<void(Cell &)> const &callback);

    void test_cell_callback(int row, int column);

    void print();
};