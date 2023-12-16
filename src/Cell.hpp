#pragma once

#include <variant>
#include <functional>
#include <string>
#include <stdexcept>

struct Color final {
    int r, g, b, a;

    [[nodiscard]] std::string as_string() const {
        // @formatter:off
        return std::string{"r:"} + std::to_string(r) +
                              "|g:" + std::to_string(g) +
                              "|b:" + std::to_string(b) +
                              "|a:" + std::to_string(a);
        // @formatter:on
    }
};

class Cell final {
    friend class Table;

    friend class TablePrinter;

private:
    using variant_ty = std::variant<int, double, std::monostate, std::string, Color>;
    using callback_ty = std::function<void(Cell &)>;
    int m_row, m_column;
    std::string m_str_value;
    variant_ty m_value{ std::monostate{ }};
    callback_ty m_callback{ [](Cell &) { }};

    void set_string_value();

public:
    Cell(int row, int column);

    template<typename T>
    [[nodiscard]] bool is_a() const {
        return std::holds_alternative<T>(m_value);
    }

    template<typename T>
    [[nodiscard]] T value() const {
        if (auto const *ptr = std::get_if<T>(&m_value)) {
            return *ptr;
        } else {
            throw std::runtime_error("type mismatch");
        }
    }

    [[nodiscard]] std::string string_value() const;

    [[nodiscard]] bool is_empty() const;

    template<typename T>
    void set_value(T value) {
        m_value = value;
        set_string_value();
        m_callback(*this);
    }

    void set_callback(callback_ty const &callback);

    void test_callback();
};