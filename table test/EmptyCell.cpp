#include "EmptyCell.hpp"

EmptyCell::EmptyCell(pos_callback_func position_callback, index_callback_func index_callback)
	: Cell{ "", position_callback, index_callback } {}

bool EmptyCell::is_empty() const {
	return true;
}

EmptyCell& EmptyCell::as_empty() {
	return *this;
}

EmptyCell const& EmptyCell::as_empty() const {
	return *this;
}
