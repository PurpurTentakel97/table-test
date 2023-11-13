#pragma once
#include "Cell.hpp"

class DoubleCell final : public Cell {
private:
	double m_value;
public:
	DoubleCell(double value, pos_callback_func position_callback, index_callback_func index_callback);

	[[nodiscard]] double value() const;
	void set_value(double value);

	void clear() override {
		m_value = 0.0;
		set_value_str(std::to_string(m_value));
	}

	// poly
	[[nodiscard]] bool is_double() const override;
	[[nodiscard]] DoubleCell& as_double() override;
	[[nodiscard]] DoubleCell const& as_double() const override;
};