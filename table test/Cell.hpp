#pragma once
#include "types.hpp"
#include <string>
#include <functional>

class EmptyCell;
class StringCell;
class IntCell;
class DoubleCell;
class ColorCell;

class Cell {
private:
	std::string m_value_str;

protected:
	using pos_callback_func = std::function<std::pair<usize, usize>(Cell*)>;
	pos_callback_func m_position_callback;
	using index_callback_func = std::function<usize(Cell*)>;
	index_callback_func m_index_callback;
	
public:
	Cell(std::string value, pos_callback_func position_callback, index_callback_func index_callback);

	[[nodiscard]] std::string const& value_str() const;

	// poly
	[[nodiscard]] virtual bool is_empty() const;
	[[nodiscard]] virtual EmptyCell& as_empty();
	[[nodiscard]] virtual EmptyCell const& as_empty() const;

	[[nodiscard]] virtual bool is_string() const;
	[[nodiscard]] virtual StringCell& as_string();
	[[nodiscard]] virtual StringCell const& as_string() const;

	[[nodiscard]] virtual bool is_int() const;
	[[nodiscard]] virtual IntCell& as_int();
	[[nodiscard]] virtual IntCell const& as_int() const;

	[[nodiscard]] virtual bool is_double() const;
	[[nodiscard]] virtual DoubleCell& as_double();
	[[nodiscard]] virtual DoubleCell const& as_double() const;

	[[nodiscard]] virtual bool is_color() const;
	[[nodiscard]] virtual ColorCell& as_color();
	[[nodiscard]] virtual ColorCell const& as_color() const;
};