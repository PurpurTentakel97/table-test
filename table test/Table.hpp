#pragma once
#include "Cells.hpp"
#include <memory>
#include <vector>

class Table final {
private:
	using usize = size_t;
	usize m_row_count, m_column_count;
	std::vector<std::shared_ptr<Cell>> m_cells;

	[[nodiscard]] usize index_from_pos(usize row, usize column) const;
	[[nodiscard]] std::pair<usize, usize> pos_from_index(usize index) const;
	[[nodiscard]] std::pair<usize, usize> pos_from_cell(Cell* cell) const;
	[[nodiscard]] usize index_from_cell(Cell* cell) const;

	[[nodiscard]] bool is_valid_pos(usize row, usize column) const;
	[[nodiscard]] bool is_valid_index(usize index) const;

public:
	Table(usize row_count, usize column_count);
};