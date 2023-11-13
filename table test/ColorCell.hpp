#pragma once
#include "Cell.hpp"

struct Color {
	int r, g, b, a;
};

class ColorCell final : public Cell {
private:
	Color m_value;
public:
	ColorCell(Color value, pos_callback_func position_callback, index_callback_func index_callback);

	[[nodiscard]] Color value() const;
 	void set_value(Color value);


	// poly
	[[nodiscard]] bool is_color() const override;
	[[nodiscard]] ColorCell& as_color() override;
	[[nodiscard]] ColorCell const& as_color() const override;
};