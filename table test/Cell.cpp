#include "Cell.hpp"
#include <stdexcept>
#include <iostream>

void Cell::set_value_str(std::string const& value_str) {
	m_value_str = std::move(value_str);
}

Cell::Cell(std::string value, pos_callback_func position_callback, index_callback_func index_callback)
	:m_value_str{ std::move(value) }, m_position_callback{ position_callback }, m_index_callback{ index_callback } { }

std::string const& Cell::value_str() const {
	return m_value_str;
}

void Cell::clear() { }

// poly
bool Cell::is_empty() const {
	return false;
}

EmptyCell& Cell::as_empty() {
	throw std::runtime_error("other cell as empty cell mut");
}

EmptyCell const& Cell::as_empty() const {
	throw std::runtime_error("other cell as empty cell const");
}

bool Cell::is_string() const {
	return false;
}

StringCell& Cell::as_string() {
	throw std::runtime_error("other cell as string cell mut");
}

StringCell const& Cell::as_string() const {
	throw std::runtime_error("other cell as string cell const");
}

bool Cell::is_int() const {
	return false;
}

IntCell& Cell::as_int() {
	throw std::runtime_error("other cell as int cell mut");
}

IntCell const& Cell::as_int() const {
	throw std::runtime_error("other cell as int cell const");
}

bool Cell::is_double() const {
	return false;
}

DoubleCell& Cell::as_double() {
	throw std::runtime_error("other cell as double cell mut");
}

DoubleCell const& Cell::as_double() const {
	throw std::runtime_error("other cell as double cell const");
}

bool Cell::is_color() const {
	return false;
}

ColorCell& Cell::as_color() {
	throw std::runtime_error("other cell as color cell mut");
}

ColorCell const& Cell::as_color() const {
	throw std::runtime_error("other cell as color cell const");
}
