#include "IntCell.hpp"
#include <iostream>

IntCell::IntCell(int value, pos_callback_func position_callback, index_callback_func index_callback)
	: Cell{ std::to_string(value), position_callback, index_callback }, m_value{ value } {}

int IntCell::value() const {
	return m_value;
}

void IntCell::set_value(int value) {
	m_value = value;
	set_value_str(std::to_string(value));
}

bool IntCell::is_int() const {
	return true;
}

IntCell& IntCell::as_int() {
	return *this;
}

IntCell const& IntCell::as_int() const {
	return *this;
}
