#include "Table.hpp"
#include "TablePrinter.hpp"

int main() {
    auto table = Table{5, 6};
    TablePrinter().print(table);
};
