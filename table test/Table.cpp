#include "Table.hpp"
#include <stdexcept>

size_t Table::index_from_pos(size_t row, size_t column) const {
	return m_column_count * row + column;
}

std::pair<usize, usize> Table::pos_from_index(usize index) const {
	auto row = index / m_column_count;
	auto column = index - index_from_pos(row, 0);
	return { row, column };
}

std::pair<usize, usize> Table::pos_from_cell(Cell* cell) const {
	auto index = index_from_cell(cell);
	return pos_from_index(index);
}

usize Table::index_from_cell(Cell* to_check) const {
	auto it = std::find_if(m_cells.begin(), m_cells.end(), [to_check](std::shared_ptr<Cell> cell) {
		return to_check == cell.get();
	});
	if (it != m_cells.end()) {
		return it - m_cells.begin();
	}
	else {
		throw std::runtime_error("invalid cell in table while getting index from cell");
	}
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
			cell->debug_print();

		}
	}
}
