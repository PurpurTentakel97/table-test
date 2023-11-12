#pragma once
#include "Cell.hpp"

class IntCell final : public Cell {
private:
	int m_value;
public:
	IntCell(int value, pos_callback_func position_callback, index_callback_func index_callback);

	// poly
	[[nodiscard]] bool is_int() const override;
	[[nodiscard]] IntCell& as_int() override;
	[[nodiscard]] IntCell const& as_int() const override;
};
