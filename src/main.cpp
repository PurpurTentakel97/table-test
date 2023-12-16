#include "Table.hpp"
#include "TablePrinter.hpp"

void callback(Cell &cell) {
    std::cout << cell.string_value() << '\n';
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
};
