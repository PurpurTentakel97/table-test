#include "Table.hpp"

void print_table(Table const& t) {
	std::cout << "\n|-->\n\n";
	t.debug_print();
}


int main() {
	auto table = Table(15, 8);

	print_table(table);

	table.set_value<int>(0, 0, 10);
	table.set_value<double>(1, 0, 1.56);
	table.set_value<std::string>(2, 0, "Hello Du!");
	table.set_value<Color>(3, 0, { 1, 5, 6, 8 });

	print_table(table);

	table.clear_cell(0, 0);
	table.clear_cell(1, 0);
	table.clear_cell(2, 0);
	table.clear_cell(3, 0);
	table.clear_cell(4, 0);

	print_table(table);
}
