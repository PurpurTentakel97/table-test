#pragma once
#include "Cell.hpp"

class DoubleCell final : public Cell {
private:
	double m_value;
public:
	DoubleCell(double value, pos_callback_func position_callback, index_callback_func index_callback);

	[[nodiscard]] double value() const;
	void set_value(double value);

	// poly
	[[nodiscard]] bool is_double() const override;
	[[nodiscard]] DoubleCell& as_double() override;
	[[nodiscard]] DoubleCell const& as_double() const override;
};