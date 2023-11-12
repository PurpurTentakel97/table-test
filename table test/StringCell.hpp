#pragma once
#include "Cell.hpp"

class StringCell final : public Cell {
private:
	std::string m_value;
public:
	StringCell(std::string value, pos_callback_func position_callback, index_callback_func index_callback);

	// poly
	[[nodiscard]] bool is_string() const override;
	[[nodiscard]] StringCell& as_string() override;
	[[nodiscard]] StringCell const& as_string() const override;
};