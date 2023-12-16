#pragma once

#include <variant>
#include <functional>
#include <string>
#include <stdexcept>

struct Color final {
	int r, g, b, a;
};

class Cell final {
	friend class Table;
private:
	int x, y;
	std::string str_value;
	std::variant<int, double, std::monostate, std::string, Color> m_value;
	std::function<void(Cell&)> callback;

public:
	Cell(int x, int y) : x{ x }, y{ y } {
		m_value = std::monostate{};
	}

	template<typename T>
	[[nodiscard]] bool is_a() const {
		return std::holds_alternative<T>(m_value);
	}

	template<typename T>
	[[nodiscard]] T& get_value() const {
		if (auto* ptr = std::get_if<T>(m_value)) {
			return *ptr;
		}
		else {
			throw std::runtime_error("type mismatch");
		}
	}

	[[nodiscard]] bool is_empty() const {
		return std::holds_alternative<std::monostate>(m_value);
	}

	void set_value(auto value) {
		m_value = value;
		callback(*this);
	}
};