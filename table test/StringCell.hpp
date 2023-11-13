#pragma once
#include "Cell.hpp"

class StringCell final : public Cell {
private:
	std::string m_value;
public:
	StringCell(std::string value, pos_callback_func position_callback, index_callback_func index_callback);

	[[nodiscard]] std::string const& value() const;
	void set_value(std::string const& value);

	void clear() override {
		m_value = "";
		set_value_str(m_value);
	}

	// poly
	[[nodiscard]] bool is_string() const override;
	[[nodiscard]] StringCell& as_string() override;
	[[nodiscard]] StringCell const& as_string() const override;
};