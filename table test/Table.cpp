#include "Table.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

size_t Table::index_from_pos(usize row, usize column) const {
	return m_column_count * row + column;
}

std::pair<usize, usize> Table::pos_from_index(usize index) const {
	auto const row    = index / m_column_count;
	auto const column = index % m_column_count;
	return { row, column };
}

std::pair<usize, usize> Table::pos_from_cell(Cell* cell) const {
	auto const index = index_from_cell(cell);
	return pos_from_index(index);
}

usize Table::index_from_cell(Cell* to_check) const {
	auto const it = std::find_if(m_cells.begin(), m_cells.end(), [to_check](std::shared_ptr<Cell> cell) {
		return to_check == cell.get();
	});
	if (it != m_cells.end()) {
		return it - m_cells.begin();
	}
	else {
		throw std::runtime_error("invalid cell in table while getting index from cell");
	}
}

bool Table::is_valid_pos(usize row, usize column) const {
	if (row    >= m_row_count   ) { return false; }
	if (column >= m_column_count) { return false; }
	return true;
}

bool Table::is_valid_index(usize index) const {
	if (index >= m_cells.size()) { return false; }
	return true;
}

Table::Table(usize row_count, usize column_count)
	: m_row_count{ row_count }, m_column_count{ column_count } {
	auto pos_cb = [this](Cell* cell) -> std::pair<usize, usize> {
		return this->pos_from_cell(cell);
	};
	auto ind_cb = [this](Cell* cell) -> usize {
		return this->index_from_cell(cell);
	};

	for (usize row_i = 0; row_i < row_count; ++row_i) {
		for (usize column_i = 0; column_i < column_count; ++column_i) {
			auto cell = std::make_shared<EmptyCell>(
				pos_cb,
				ind_cb
			);
			m_cells.push_back(cell);
		}
	}
}

void Table::debug_print() const {
	usize span{ 15 };
	for (usize row_i = 0; row_i < m_row_count; ++row_i) {
		std::cout << '+';
		for (usize col_i = 0; col_i < m_column_count; ++col_i) {
			std::cout << std::string( span + 2, '-' );
			if (col_i + 1 != m_column_count) {
				std::cout << '+';
			}
		}
		std::cout << "+\n";

		std::cout << "| ";
		for (usize col_i = 0; col_i < m_column_count; ++col_i) {
			std::cout << std::left <<  std::setw(span + 1) << m_cells[index_from_pos(row_i, col_i)]->value_str();
			if (col_i + 1 != m_column_count) {
				std::cout << "| ";
			}
		}
		std::cout << "|\n";
	}
	std::cout << '+';
	for (usize col_i = 0; col_i < m_column_count; ++col_i) {
		std::cout << std::string(span + 2, '-');
		if (col_i + 1 != m_column_count) {
			std::cout << '+';
		}
	}
	std::cout <<  "+\n";

}
