#pragma once
#include "Cell.hpp"

class EmptyCell final : public Cell {
private:
public:
	EmptyCell(pos_callback_func position_callback, index_callback_func index_callback);

	// poly
	[[nodiscard]] bool is_empty() const override;
	[[nodiscard]] EmptyCell& as_empty() override;
	[[nodiscard]] EmptyCell const& as_empty() const override;
};