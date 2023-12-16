#include "Table.hpp"
#include "TablePrinter.hpp"

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

int main() {
    auto table = Table{ 5, 4 };

    table.set_cell_callback(2, 2, callback);
    table.set_cell_callback(1, 3, callback);
    table.set_cell_callback(4, 0, callback);
    table.set_cell_callback(0, 1, callback);

    table.set_value(2, 2, "Hello World!");
    table.set_value(1, 3, 3.56);
    table.set_value(4, 0, 10);
    table.set_value(0, 1, Color(1, 5, 6, 9));

    TablePrinter::print(table);

    table.clear_cell(2, 2);
    TablePrinter::print(table);
};
