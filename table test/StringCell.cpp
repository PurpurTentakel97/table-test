#include "StringCell.hpp"

StringCell::StringCell(std::string value, pos_callback_func position_callback, index_callback_func index_callback)
	: Cell{ value, position_callback, index_callback }, m_value{ std::move(value) } {}

bool StringCell::is_string() const {
	return true;
}

StringCell& StringCell::as_string() {
	return *this;
}

StringCell const& StringCell::as_string() const {
	return *this;
}
