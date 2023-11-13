#include "Table.hpp"

int main() {
	auto table = Table(15, 8);
	table.debug_print();
	table.set_value<int>(0, 0, 10);
	table.set_value<double>(1, 0, 1.56);
	table.set_value<std::string>(2, 0, "Hello Du!");
	table.set_value<Color>(3, 0, { 1, 5, 6, 8 });
	table.debug_print();
}
