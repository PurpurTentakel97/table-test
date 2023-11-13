#include "ColorCell.hpp"

ColorCell::ColorCell(Color value, pos_callback_func position_callback, index_callback_func index_callback)
	: Cell{ "Color", position_callback, index_callback }, m_value{ value } {}

Color ColorCell::value() const {
	return m_value;
}

void ColorCell::set_value(Color value) {
	m_value = value;
}

bool ColorCell::is_color() const {
	return true;
}

ColorCell& ColorCell::as_color() {
	return *this;
}

ColorCell const& ColorCell::as_color() const {
	return *this;
}
