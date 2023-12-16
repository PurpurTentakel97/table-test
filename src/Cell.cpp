
#include "Cell.hpp"

void Cell::set_string_value() {
    if (is_a<Color>()) {
        m_str_value = value<Color>().as_string();
    } else if (is_a<std::string>()) {
        m_str_value = value<std::string>();
    } else if (is_a<int>()) {
        m_str_value = std::to_string(value<int>());
    } else if (is_a<double>()) {
        m_str_value = std::to_string(value<double>());
    } else if (is_a<std::monostate>()) {
        m_str_value.clear();
    }
}

Cell::Cell(int row, int column) : m_row{ row }, m_column{ column } {
}

std::string Cell::string_value() const {
    return m_str_value;
}

bool Cell::is_empty() const {
    return std::holds_alternative<std::monostate>(m_value);
}

void Cell::set_callback(Cell::callback_ty const &callback) {
    m_callback = callback;
}

void Cell::test_callback() {
    m_callback(*this);
}

void Cell::clear() {
    set_value(std::monostate());
}



