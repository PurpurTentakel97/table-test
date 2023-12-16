
#include "Cell.hpp"

Cell::Cell(int x, int y) : x{x}, y{y} {
    m_value = std::monostate{};
}

bool Cell::is_empty() const {
    return std::holds_alternative<std::monostate>(m_value);
}

