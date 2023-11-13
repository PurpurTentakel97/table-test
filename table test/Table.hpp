#pragma once
#include "Cells.hpp"
#include <memory>
#include <iostream>
#include <concepts>
#include <vector>

template<typename T>
struct value_to_cell;

template<>
struct value_to_cell<void> {
	using Type = EmptyCell;
};

template<>
struct value_to_cell<std::string> {
	using Type = StringCell;
};

template<>
struct value_to_cell<int> {
	using Type = IntCell;
};

template<>
struct value_to_cell<double> {
	using Type = DoubleCell;
};

template<>
struct value_to_cell<Color> {
	using Type = ColorCell;
};

class Table final {
private:
	using usize = size_t;
	usize m_row_count, m_column_count;
	std::vector<std::shared_ptr<Cell>> m_cells;

	using pos_cb_ty = std::function<std::pair<usize, usize>(Cell*)>;
	pos_cb_ty m_pos_cb;
	using ind_cb_ty = std::function<usize(Cell*)>;
	ind_cb_ty m_ind_cb;

	[[nodiscard]] usize index_from_pos(usize row, usize column) const;
	[[nodiscard]] std::pair<usize, usize> pos_from_index(usize index) const;
	[[nodiscard]] std::pair<usize, usize> pos_from_cell(Cell* cell) const;
	[[nodiscard]] usize index_from_cell(Cell* cell) const;

	[[nodiscard]] bool is_valid_pos(usize row, usize column) const;
	[[nodiscard]] bool is_valid_index(usize index) const;

public:
	Table(usize row_count, usize column_count);

	void debug_print() const;
	void clear_cell(usize row, usize column) const;

	template<typename value_ty, typename cell_ty = value_to_cell<value_ty>::Type>
	void set_value(usize row, usize column, value_ty value) {
		if (cell_ty* cell = dynamic_cast<cell_ty*>(m_cells[index_from_pos(row, column)].get())){
			cell->set_value(value);
		}
		else {
			m_cells[index_from_pos(row, column)] = (std::make_shared<cell_ty>(
				value,
				m_pos_cb,
				m_ind_cb
			));
		}
	}
};