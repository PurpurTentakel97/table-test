#include "Table.hpp"
#include <sstream>
#include <iostream>

void callback(Cell &cell) {
    std::stringstream s{ };
    s << "current_value: " << cell.string_value() << '\n';
    s << "old_value: ";
    if (cell.is_a_old<Color>()) {
        s << cell.old_value<Color>().as_string();
    } else if (cell.is_a_old<std::monostate>()) {
        s << "void";
    } else if (cell.is_a_old<double>()) {
        s << std::to_string(cell.old_value<double>());
    } else if (cell.is_a_old<int>()) {
        s << std::to_string(cell.old_value<int>());
    } else if (cell.is_a_old<std::string>()) {
        s << cell.old_value<std::string>();
    }

    std::cout << s.str() << '\n';;
}

static inline const std::function<void(std::string const &)> tag({ [](std::string const &m) -> void {
    std::cout << "[[" << m << "]]\n";
}});


int main() {
    auto table = Table{ 5, 4 };
    table.set_numbered_table(true);
    table.print();
};
