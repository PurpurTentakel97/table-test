#include "DoubleCell.hpp"

DoubleCell::DoubleCell(double value, pos_callback_func position_callback, index_callback_func index_callback)
	: Cell{ std::to_string(value), position_callback, index_callback }, m_value{ value } {}

double DoubleCell::value() const {
	return m_value;
}

void DoubleCell::set_value(double value) {
	m_value = value;
	set_value_str(std::to_string(value));
}

bool DoubleCell::is_double() const {
	return true;
}

DoubleCell& DoubleCell::as_double() {
	return *this;
}

DoubleCell const& DoubleCell::as_double() const {
	return *this;
}
